#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -Wvla -o app_unit.exe src/utils.c unit_testing.c
