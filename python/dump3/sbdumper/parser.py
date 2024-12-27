#!/usr/bin/env python3
import argparse
import sys
import os

# Define ANSI color codes
BLUE    = '\033[34m'
GREEN   = '\033[32m'
RED     = '\033[31m'
RESET   = '\033[0m'

DATE                    = "2024-11-11"
PROGAM_STR              = "SBDumper"
VERSION_STR             = "0.1.0"
INFO                    = "A Servebolt AS based multi-threaded MySQL/MariaDB database export-/importer"
DESCRIPTION             = f"{PROGAM_STR} v{VERSION_STR} - {INFO}"
VERSION_INFO            = f"{PROGAM_STR} v{VERSION_STR}"
VERBOSE_VERSION_INFO    = f"""
Name:       {PROGAM_STR}
Version:    {VERSION_STR}
Stripped:   {VERSION_STR.replace('.', '')}
Pretty:     {PROGAM_STR} v{VERSION_STR}
Info:       {INFO}
Date:       {DATE}
Author:     Oskar Voldbakken Hesle
Owner:      Servebolt AS"""

if (("--version" in sys.argv or "-v" in sys.argv) and 
    ("--verbose" in sys.argv or "-V" in sys.argv) or 
    ("-Vv" in sys.argv or "-vV" in sys.argv)):
    VERSION_FINAL = VERBOSE_VERSION_INFO
else:
    VERSION_FINAL = DESCRIPTION

class CustomArgumentFormatter(argparse.RawTextHelpFormatter):
    def __init__(self, prog: str, indent_increment: int = 2, max_help_position: int = 60, width: int | None = None) -> None:
        super().__init__(prog, indent_increment, max_help_position, width)

    def format_help(self) -> str:
        help_text = super().format_help()
        help_text = help_text.replace("positional arguments", f"{GREEN}Positional Arguments{RESET}").replace("usage:", f"{GREEN}Usage{RESET}:").replace("options:", f"{GREEN}Normal Options{RESET}:")
        return help_text

parser = argparse.ArgumentParser(description=DESCRIPTION, formatter_class=CustomArgumentFormatter, add_help=False)
parser.add_argument("--help", action="help", help="Show this and exit")
parser.add_argument("-v", "--version", action="version", version=VERSION_FINAL, help="Show version info")
parser.add_argument("-V", "--verbose", action="store_true", help="Messages will have more info")
parser.add_argument("-t", "--threads", type=int, default=1, help="Choose how many threads to run. Default 1")
parser.add_argument(f"{BLUE}shorthand_import{RESET}", nargs='?', help="[ssh_user@ssh_host[:ssh_port]$][username[:password]@]database[:host[:port]]")
parser.add_argument(f"{RED}shorthand_export{RESET}", nargs='?', help="[username[:password]@]database[:host[:port]]")

import_group = parser.add_argument_group(f"{BLUE}Import Options{RESET}")
import_group.add_argument("-d", "--database-import", "--dbi", help=f"Database for {BLUE}import{RESET}")
import_group.add_argument("-h", "--hostname-import", "--hoi", default="localhost", help=f"Hostname for database {BLUE}import{RESET}. Default: localhost")
import_group.add_argument("-u", "--username-import", "--usi", default=os.getlogin(), help=f"Username for database {BLUE}import{RESET}. Default: {os.getlogin()}")
import_group.add_argument("-p", "--password-import", "--psi", help=f"Password for database {BLUE}import{RESET}")
import_group.add_argument("-r", "--portnumber-import", "--ori", type=int, default=3306, help=f"Port number for database {BLUE}import{RESET}. Default: 3306")
import_group.add_argument("-s", "--sshtunnel-import", "--sti", help="Use a SSH tunnel to connect to the importing database")

export_group = parser.add_argument_group(f"{RED}Export Options{RESET}")
export_group.add_argument("-D", "--database-export", "--dbe", help="Database name to export to")
export_group.add_argument("-H", "--hostname-export", "--hoe", default="localhost", help="Hostname for the database to export from")
export_group.add_argument("-U", "--username-export", "--use", default=os.getlogin(), help="Username for the database to export from")
export_group.add_argument("-P", "--password-export", "--pse", help="Password for the exporting database username")
export_group.add_argument("-R", "--portnumber-export", "--ore", type=int, default=3306, help="Port number for the exporting database hostname. Default: 3306")
export_group.add_argument("-S", "--sshtunnel-export", "--ste", help="Use a SSH tunnel to connect to the exporting database")
args = parser.parse_args()
