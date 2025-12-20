from io import TextIOWrapper
from datetime import datetime
from pathlib import Path
import sys

LIB_VER = 2
LIB_SRC = Path("zlog")
LIB_OUT = f"zlog_v{LIB_VER}.hpp"

includes: set[str] = set()


def write_desc(f: TextIOWrapper) -> None:
    f.writelines([
        "/*\n\n"
        "=== ZLOG -> C++ 23 LOGGING LIBRARY ===\n\n",
        "--- Details ---\n\n",
        f"version: {LIB_VER}\n",
        f"date:    {datetime.today().strftime("%d-%m-%Y")}\n",
        "author:  https://www.github.com/SelvamKrishna\n\n"
        "*/"
    ])


def write_from_file(f_out: TextIOWrapper, from_file: str) -> None:
    global includes
    f_out.write("\n")

    with open(from_file, 'r') as f_in:
        LINES = f_in.readlines()
        start_idx = 1

        while True:
            line = LINES[start_idx]

            if line.strip().startswith("namespace"):
                break

            if line not in includes and '"' not in line:
                f_out.write(line)

            includes.add(line)
            start_idx += 1

        f_out.write("\n")

        f_out.writelines([
            line
            for (i, line) in enumerate(LINES)
            if i > start_idx - 1
        ])


def full_combine() -> None:
    with open(LIB_OUT, 'w') as f:
        f.write("#pragma once\n\n")
        write_desc(f)

        for f_src in LIB_SRC.iterdir():
            if f_src.is_file():
                write_from_file(f, f_src)


def part_combine() -> None:
    with open(LIB_OUT, 'w') as f:
        f.write("#pragma once\n\n")
        write_desc(f)

        f.write("\n\n")
        for file_name in LIB_SRC.iterdir():
            if file_name.is_file():
                f.write(f"#include \"{file_name}\" // IWYU pragma: keep\n")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        HELP_MSG = [
            "Help:",
            "  'python ./build.py full' - Fully combined header file",
            "  'python ./build.py part' - Partially combined header file"
        ]

        for line in HELP_MSG:
            print(line)
    else:
        part_combine() if "part" in sys.argv else full_combine()
