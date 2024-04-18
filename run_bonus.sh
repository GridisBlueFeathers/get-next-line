#!/bin/bash

cc ./get_next_line_bonus.c ./get_next_line_utils_bonus.c -o test -D BUFFER_SIZE=${1:-42} && ./test
