#!/bin/bash

is_file_valid() {
    file=$1
    if ! [ -f "$file" ]; then
        exit 2 # existance error
    elif ! [ -r "$file" ]; then
        exit 3 # permission error
    fi
}

input_file=$1
output_file=$2

is_file_valid "$input_file"
is_file_valid "$output_file"

# app.exe existance
if [[ -f "../../app.exe" ]]; then
    ./../../app.exe "$input_file" > pos_actual_output.txt
    comparison=$(./comparator.sh "$output_file" pos_actual_output.txt)
else
    echo "test: ./app.exe: No such file or directory"
    exit 4
fi

if [ "$comparison" != 0 ]; then
    exit 1
fi

exit 0
