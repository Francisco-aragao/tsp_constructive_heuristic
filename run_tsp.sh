#!/bin/bash

# Prompt the user to enter the folder path
read -p "Enter the folder path: " INPUT_FOLDER

# Check if the input folder exists
if [ ! -d "$INPUT_FOLDER" ]; then
    echo "Error: Input folder '$INPUT_FOLDER' does not exist."
    exit 1
fi

# Iterate over all files in the input folder that end with ".tsp"
for file in "$INPUT_FOLDER"/*.tsp; do
    # Check if any .tsp files exist
    if [ ! -e "$file" ]; then
        echo "No .tsp files found in folder: $INPUT_FOLDER"
        break
    fi

    # Process the file
    echo ""
    echo "Processing file: $file"
    ./saida < "$file"
done
