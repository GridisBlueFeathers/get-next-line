#!/bin/bash

cc ./get_next_line.c ./get_next_line_utils.c -o test -D BUFFER_SIZE=${1:-42} && ./test
