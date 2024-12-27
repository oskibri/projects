#!/usr/bin/env python3
import argparse
import sys

version_info = {
    "name": "dumptrunc",
    "num": "010",
    "vernum": "0.1.0",
    "owner": "Servebolt AS",
    "author": "Oskar Voldbakken Hesle",
    "date": "2024-11-13"
}
version_info["fullname"] = f"{version_info['name']} v{version_info['vernum']}"

parser = argparse.ArgumentParser(
    description="Truncate MySQL/MariaDB dump files to fit within a specified packet size. Default = 16MB",
    usage="%(prog)s [-h] [-v] [-V] [-i] [-o OUTPUT] input")
parser.add_argument('input', nargs='?', help="file to read from")
parser.add_argument('-v', '--version', action='store_true', help="show version info. -V for full version info")
parser.add_argument('-i', '--inplace', action='store_true', help="change input file in-place")
parser.add_argument('-o', '--output', help="output file to populate with changes")
parser.add_argument('-V', '--full-version', action='store_true', help=argparse.SUPPRESS)
args = parser.parse_args()

if len(sys.argv) == 1:
    parser.print_help()
    sys.exit(0)
elif args.version:
    print(f"{version_info['name']} v{version_info['vernum']} {version_info['date']} - {version_info['owner']}")
    sys.exit(0)
elif args.full_version:
    [print(f"{key.upper() + ':':<10} {value}") for key, value in version_info.items()]
    sys.exit(0)
elif not args.input and not (args.version or args.full_version):
    parser.error("\x1b[31mthe following argument is required: input\x1b[0m")
