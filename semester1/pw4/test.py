"""
          ╔═╤═╗
          ║ │ ║
╔═════════╬═╪═╬═╗
║         ║ │ ║ ║
║         ║ │ ║ ║
║         ║ │ ║ ║
╟─────────╫─┼─╫─╢
║         ║ │ ║ ║
║         ║ │ ║ ║
║         ║ │ ║ ║
╚═════════╬═╪═╬═╝
          ║ │ ║
          ╚═╧═╝
"""

borders_h = [" ", "─", "═"]
borders_v = [" ", "│", "║"]
cross = {
    (0, 0, 0, 0): " ",
    # sec intercept
    (2, 1, 2, 1): "╫",
    (1, 2, 1, 2): "╪",
    # sec intercept 2
    (2, 2, 2, 2): "╬",
    (0, 2, 2, 2): "╦",
    (2, 0, 2, 2): "╣",
    (2, 2, 0, 2): "╩",
    (2, 2, 2, 0): "╠",
    # sec intercept 1
    (1, 1, 1, 1): "┼",
    (0, 1, 1, 1): "┬",
    (1, 0, 1, 1): "┤",
    (1, 1, 0, 1): "┴",
    (1, 1, 1, 0): "├",
    # sec intercept 2 and 1
    (0, 2, 1, 2): "╤",
    (2, 0, 2, 1): "╢",
    (1, 2, 0, 2): "╧",
    (2, 1, 2, 0): "╟",
    # sec intercept 1 and 2
    (0, 1, 2, 1): "╥",
    (1, 0, 1, 2): "╡",
    (2, 1, 0, 1): "╨",
    (1, 2, 1, 0): "╞",
    # sec intercept 2 and 0
    (0, 2, 0, 2): "═",
    (2, 0, 2, 0): "║",
    # sec intercept 1 and 0
    (0, 1, 0, 1): "─",
    (1, 0, 1, 0): "│",
    # sec 1
    (1, 1, 0, 0): "└",
    (0, 1, 1, 0): "┌",
    (0, 0, 1, 1): "┐",
    (1, 0, 0, 1): "┘",
    # sec 2
    (2, 2, 0, 0): "╚",
    (0, 2, 2, 0): "╔",
    (0, 0, 2, 2): "╗",
    (2, 0, 0, 2): "╝",
    # sec 2->1
    (2, 1, 0, 0): "╙",
    (0, 2, 1, 0): "╒",
    (0, 0, 2, 1): "╖",
    (1, 0, 0, 2): "╛",
    # sec 1->2
    (1, 2, 0, 0): "╘",
    (0, 1, 2, 0): "╓",
    (0, 0, 1, 2): "╕",
    (2, 0, 0, 1): "╜",
}


def get_cross(neighbors):
    return cross[neighbors]


def build_framework(h_config, v_config, h_size=1, v_size=1):
    result = ""
    w, h = len(h_config), len(v_config)
    for i in range(h):
        v_line = ""
        for j in range(w):
            top = v_config[j][i - 1] if i - 1 >= 0 else 0
            bottom = v_config[j][i] if i < w - 1 else 0

            left = h_config[i][j - 1] if j - 1 >= 0 else 0
            right = h_config[i][j] if j < h - 1 else 0

            v_line += borders_v[bottom] + " " * h_size

            neighbors = (top, right, bottom, left)
            cross = get_cross(neighbors)

            h_elem = borders_h[right] * h_size if j < h - 1 else ""
            result += cross + h_elem
        result += "\n"
        result += ((v_line + "\n") * v_size) if i < w - 1 else ""

    return result


def test1():
    h = [
        [0, 2, 2, 0],
        [2, 2, 2, 2],
        [1, 1, 1, 1],
        [2, 2, 2, 2],
        [0, 2, 2, 0],
    ]

    v = [
        [0, 2, 2, 0],
        [2, 2, 2, 2],
        [1, 1, 1, 1],
        [2, 2, 2, 2],
        [0, 2, 2, 0],
    ]

    print(build_framework(h, v, 15, 6))


def test2():
    h = [
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 1],
    ]

    v = [
        [1, 1, 1, 1],
        [0, 1, 0, 1],
        [1, 0, 1, 0],
        [0, 1, 0, 1],
        [1, 1, 1, 1],
    ]

    result = build_framework(h, v, 15, 6)
    print(result)


def main():
    test2()


if __name__ == "__main__":
    main()
