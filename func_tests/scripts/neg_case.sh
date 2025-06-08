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
is_file_valid "$input_file"
 
# app.exe existance
if [[ -f "../../app.exe" ]]; then
    ./../../app.exe < "$input_file" > neg_actual_output.txt
    if [[ $? -ne 0 ]]; then
        exit 0
    fi
    exit 1
else
    echo "test: ./app.exe: No such file or directory"
    exit 4
fi
