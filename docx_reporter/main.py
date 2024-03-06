import click
from docxtpl import DocxTemplate, InlineImage
import marko
from marko import Markdown
import tomllib
from g4f.client import Client
import time
import re
from dataclasses import dataclass, field
from typing import Any
from pprint import pprint

import os
from datetime import datetime
from pathlib import Path


def generate_text(prompt: str, model: str = "gpt-3.5-turbo"):
    client = Client()

    while True:
        try:
            response = client.chat.completions.create(
                model=model,
                messages=[{"role": "user", "content": prompt}],
            )
            break
        except RuntimeError:
            time.sleep(1)

    return [choice.message.content for choice in response.choices]


@dataclass
class ParserContext(object):
    source_dir: Path
    context: dict[str, Any] = field(default_factory=dict)


class Processor:
    def __init__(self, context: ParserContext):
        self.context = context


class OptionVariableProcessor(Processor):
    def parse(self, text) -> None | str:
        pattern = re.compile(r"^([^\s]+)\s+(.*)$")
        rematch = re.match(pattern, text)

        if rematch is None:
            return None

        var = rematch.group(1)
        val = rematch.group(2).strip()
        self.context.context[var] = val


class OptionPromptProcessor(Processor):
    def parse(self, text) -> None | str:
        return generate_text(text)[0]


class OptionEvaluateProcessor(Processor):
    def parse(self, text) -> None | str:
        context = self.context.context
        return eval(text)


class OptionFileLoaderProcessor(Processor):
    def parse(self, path) -> None | str:
        path = self.context.source_dir / path
        if not path.exists():
            print("Failed to load file: {}".format(path))
            return None

        return path.read_text()


def OptionLambdaProcessor(func):
    class LambdaProcessor(Processor):
        def parse(self, text) -> None | str:
            return func(text)

    return LambdaProcessor


class OptionProcessor(Processor):
    apps = {
        "s": OptionVariableProcessor,
        "p": OptionPromptProcessor,
        "e": OptionEvaluateProcessor,
        "l": OptionFileLoaderProcessor,
        "lc": OptionFileLoaderProcessor,
        "upper": OptionLambdaProcessor(str.upper),
        "lower": OptionLambdaProcessor(str.lower),
    }

    def parse(self, node) -> None | str:
        options = "|".join(self.apps.keys())
        pattern = re.compile(rf"^({options})\s+(.*)$")

        if not isinstance(node.children[0], marko.block.Paragraph):
            return None

        if not isinstance(node.children[0].children[0], marko.inline.RawText):
            return None

        option_command = node.children[0].children[0].children
        rematch = re.match(pattern, option_command)
        if rematch is None or (option_name := rematch.group(1)) not in self.apps:
            return None

        processor = self.apps[option_name](self.context)
        return processor.parse(rematch.group(2))


class MarkdownToDocxProcessor(Processor):
    def __init__(self, template, source_dir: Path, context=None):
        self.template_path = template
        self.template = DocxTemplate(template)
        
        context = {
            **self.load_default_context(),
            **(context or {}),
        }
        self.context = ParserContext(source_dir=source_dir, context=context)

    def load_default_context(cls):
        current_date = datetime.now()
        return {
            "year": current_date.year,
            "month": current_date.month,
            "day": current_date.day,
            "hour": current_date.hour,
            "minute": current_date.minute,
            "second": current_date.second,
        }
        
    def render(self, md):
        context = self.parse(md)
        pprint(context)
        self.template.render(context)
        
        return self.template
    
    def save(self, directory):
        filename = self.template_path.name.format(**self.context.context)
        self.template.save(directory/filename)

    def parse(self, md):
        context = self.context.context
        md_ast = Markdown().parse(md)

        current_context_var = None

        for node in md_ast.children:
            current_val = None
            print(node)
            if isinstance(node, marko.block.Paragraph):
                current_val = []
                for child in node.children:
                    if isinstance(child, marko.inline.RawText):
                        current_val.append(child.children)
                    elif isinstance(child, marko.inline.Image):
                        image_path = (self.context.source_dir / child.dest).resolve()
                        current_val.append(InlineImage(self.template, str(image_path)))

                if len(current_val) == 1:
                    current_val = current_val[0]
                else:
                    try:
                        current_val = "\n".join(current_val)
                    except TypeError:
                        ...

            if isinstance(node, marko.block.Quote):
                current_val = OptionProcessor(self.context).parse(node)

            if isinstance(node, marko.block.Heading):
                current_context_var = node.children[0].children
                context[current_context_var] = []
                continue

            if current_context_var is None:
                continue

            if current_val is None:
                continue
            context[current_context_var].append(current_val)

        for key in context:
            if not isinstance(context[key], list):
                continue
            
            if len(context[key]) == 1:
                context[key] = context[key][0]
            else:
                try:
                    context[key] = "\n".join(context[key])
                except TypeError:
                    continue

        return context


def load_config(config_path):
    if config_path is None:
        return None

    with open(str(config_path), "rb") as f:
        return tomllib.load(f)


def load_context_from_config(config):
    if config is None:
        return {}
    return config.get("setup", {}).copy()


@click.command()
@click.option(
    "-c",
    "--config",
    type=click.Path(exists=True, resolve_path=True),
    help="Source directory",
    default=None,
    callback=lambda ctx, param, val: load_config(val),
)
@click.option(
    "-t",
    "--template",
    required=True,
    type=click.Path(exists=True),
    help="Template of report",
)
@click.option(
    "-s",
    "--source-directory",
    required=True,
    type=click.Path(exists=True),
    help="Source directory",
)
def main(
    config,
    template,
    source_directory,
):
    source_directory = Path(source_directory).resolve()
    template = Path(template)

    report = source_directory / "report.md"
    if not report.exists():
        raise FileNotFoundError(f"File {report} not found")

    md = report.read_text()

    context = load_context_from_config(config)
    doc = MarkdownToDocxProcessor(template, source_directory, context)
    
    doc.render(md)

    if not (source_directory / "build").exists():
        os.mkdir(source_directory / "build")
    doc.save(source_directory / "build")


if __name__ == "__main__":
    main()
