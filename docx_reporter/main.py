import click
from docxtpl import DocxTemplate
import tomllib

import os
from datetime import datetime
from functools import lru_cache
from enum import Enum
from pathlib import Path

global config_path

PROJECT_PATH = Path(__file__).parent


def get_current_year():
    return datetime.now().year


@lru_cache()
def load_config():
    global config_path

    with open(str(config_path), "rb") as f:
        return tomllib.load(f)


class DefaultFromConfig(click.Option):
    def __init__(self, *args, **kwargs):
        kwargs["help"] = (
            kwargs.get("help", "") + "Option can also be passed from config.toml file"
        )
        super(DefaultFromConfig, self).__init__(*args, **kwargs)

    def handle_parse_result(self, ctx, opts, args):
        config = load_config()
        if self.name in config:
            self.default = config[self.name]

        return super(DefaultFromConfig, self).handle_parse_result(ctx, opts, args)


def save_config(ctx, param, value):
    global config_path
    config_path = value


class ReportType(Enum):
    lab: str = "lab"
    pz: str = "pz"

    @classmethod
    def values(cls):
        return [x.value for x in cls]


@click.command()
@click.option(
    "-C",
    "--config",
    required=True,
    type=click.Path(exists=True, resolve_path=True),
    default=PROJECT_PATH / "config.toml",
    help="Source directory",
    callback=save_config,
)
@click.option(
    "-T",
    "--template",
    required=True,
    type=click.Path(exists=True),
    default=PROJECT_PATH / "template.docx",
    help="Template of report",
)
@click.option(
    "-S",
    "--source-directory",
    required=True,
    type=click.Path(exists=True),
    help="Source directory",
)
@click.option("--full-name", prompt="Full name", type=str, cls=DefaultFromConfig)
@click.option("--variant", prompt="Variant", type=int, cls=DefaultFromConfig)
@click.option("--group", prompt="Group", type=str, cls=DefaultFromConfig)
@click.option(
    "-t",
    "--report-type",
    prompt="Report type",
    type=click.Choice(ReportType.values(), case_sensitive=False),
    help="",
)
@click.option("-n", "--report-number", prompt="Report number", type=int, help="")
@click.option("--report-theme", prompt="Report theme", type=str, help="")
def main(
    config,
    template,
    source_directory,
    report_type,
    report_number,
    report_theme,
    full_name,
    variant,
    group,
):
    source_directory = Path(source_directory)
    if not (source_directory / "report").exists():
        os.mkdir(source_directory / "report")

    doc = DocxTemplate(template)

    report_theme = report_theme.upper()
    report_type = ReportType(report_type)
    student_last_name = full_name.split(" ")[0]

    report_title_fmt = f"{{name}} №{report_number}"
    report_name_fmt = (
        f"Пр_{{name}}{report_number}_{group.replace('-', '')}_{student_last_name}"
    )

    match report_type:
        case ReportType.lab:
            report_title = report_title_fmt.format(name="лабораторної роботи")
            report_name = report_name_fmt.format(name="Лб")

        case ReportType.pz:
            report_title = report_title_fmt.format(name="практичної роботи")
            report_name = report_name_fmt.format(name="Пз")

    context = dict(
        student_full_name=full_name,
        variant=str(variant),
        group=group,
        title=report_title,
        theme=report_theme,
        year=str(get_current_year()),
    )

    doc.render(context)
    doc.save(source_directory / "report" / f"{report_name}.docx")


if __name__ == "__main__":
    main()
