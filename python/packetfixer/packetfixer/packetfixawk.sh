#!/bin/bash
# Define variables for line number (L) and byte position (N)
L=1
N=50
file="$1"

# Use awk to process the file, split the line, and insert a newline
awk -v line=$L -v byte=$N '{
    if (NR == line) {
        # Split the line into two parts and add a newline at byte position
        print substr($0, 1, byte) "\n" substr($0, byte + 1)
    } else {
        # Print the line as is for all other lines
        print $0
    }
}' "$file" > tmpfile 
#&& mv tmpfile "$file"

