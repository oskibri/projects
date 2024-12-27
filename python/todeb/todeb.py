import re
from datetime import datetime

input_str = "### Thu 05 Sep Oskar VH <oskar@servebolt.com> - `v1.3.0`"

match = re.match(r"### (\w{3} \d{2} \w{3}) (.+) <(.+)>", input_str)
if match:
    date_str, name, email = match.groups()
    
    date_obj = datetime.strptime(date_str, "%a %d %b").date()
    
    current_time = datetime.now().astimezone().strftime("%Y %H:%M:%S %z")
    formatted_date = date_obj + current_time

    output_str = f"-- Oskar Voldbakken Hesle <{email}>  {formatted_date}"
    print(output_str)
else:
    print("Input string format not recognized.")

