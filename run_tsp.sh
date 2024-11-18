#!/bin/bash

# Define the folder containing the input files
INPUT_FOLDER="./tsp_input/EUC_2D"

# Check if the input folder exists
if [ ! -d "$INPUT_FOLDER" ]; then
    echo "Error: Input folder '$INPUT_FOLDER' does not exist."
    exit 1
fi

# Iterate over all files in the input folder
for file in "$INPUT_FOLDER"/*; do
    # Check if it is a regular file
    if [ -f "$file" ]; then
        echo ""
        echo "Processing file: $file"
        ./saida < "$file"
    else
        echo "Skipping non-regular file: $file"
    fi
done