#!/bin/bash

# Get the signature of the old.txt file
rdiff signature old.txt old.sig

# Get a delta file by comparing the signature of the old.txt file, with the new.txt file
rdiff delta old.sig new.txt delta.diff

# Patch the old.txt file with the changes from the delta.diff file, and output result to updated.txt
rdiff patch old.txt delta.diff updated.txt
