#!/usr/bin/env python3
from parser import args, parser
import sys
import re

def trunc_file(input, output):
    lines = []

    if not output:
        output = input

    try:
        with open(input, 'r') as file:
            lines = file.readlines()
            index = 0
            for index, line in enumerate(lines):
                if re.match(r'^(INSERT|\()', line) and not line.endswith(';\n'):
                    lines[index] = line.replace('\n', '')


    except OSError as e:
        print(f"Failed to read from input file with error:\n{e}", file=sys.stderr)

    try:
        new_lines = [""]
        new_lines_index = 0 
        with open(output, 'w') as output:
            for index, line in enumerate(lines):
                if not line.endswith('\n') or line.endswith(');\n'):
                    new_lines[new_lines_index] += line
                    if line.endswith(');\n'):
                        new_lines_index += 1
                        new_lines.append("")
                        continue
                #output.write(line)
        [print(l, end='') for l in new_lines]
    except OSError as e:
        print(f"Failed to write to output file with error:\n{e}", file=sys.stderr)

def main():
    input = args.input or False
    output = args.output or False

    # Failsafe if parser fails at some point
    if not (input or output):
        print(f"\x1b[31mEither or both input and output isn't specified\nInput: {input}\nOutput: {output}\x1b[0m", file=sys.stderr)
        parser.print_help()
        sys.exit(1)

    trunc_file(input, output)

if __name__ == "__main__":
    main()
