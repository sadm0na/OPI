#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -o app.exe ./src/*.c
