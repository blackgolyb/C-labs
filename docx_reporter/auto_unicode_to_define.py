import sys
import requests
from bs4 import BeautifulSoup
import re


URL_FMT = "https://www.compart.com/en/unicode/U+{num}"

def extract_char(html):
    soup = BeautifulSoup(html)
    
    name_label = soup.find('td', text = re.compile('Name:'))
    name = name_label.parent.contents[1].contents[0].text
    
    code_label = soup.find('td', text = re.compile('UTF-8 Encoding:'))
    code = code_label.parent.find('code').text
    code = code.split()
    
    char_div = soup.find('div', attrs={"class": "letter card"})    
    char = char_div.contents[0].text
    
    return name, code, char

def make_define_from_code(name, code):
    name = "_".join(name.upper().split())
    code = "".join(map(lambda x: x.replace("0x", "\\x"), code))
    return f"#define {name} L'{code}'"

def make_define_from_char(name, char):
    name = "_".join(name.upper().split())
    return f"#define {name} L'{char}'"

def main():
    try:
        start, end  = sys.argv[1:3]
    except ValueError:
        print("Usage: python3 main.py <start> <end>")
        exit(1)
        
    print(int(start, base=16), int(end, base=16))    
    
    return 
    
    codes_defs = []
    chars_defs = []
    
    chars_range = range(int(start, base=16), int(end, base=16))
    
    for char in chars_range:
        hex_code = hex(char)[2:]
        url = URL_FMT.format(num=hex_code)

        name, code, char = extract_char(requests.get(url).text)
        
        codes_defs.append(make_define_from_code(name, code))
        chars_defs.append(make_define_from_char(name, char))

    with open("codes_defs.txt", "w") as f:
        print("\n".join(codes_defs), file=f)
    
    with open("chars_defs.txt", "w") as f:
        print("\n".join(chars_defs), file=f)
    
if __name__ == '__main__':
    main()