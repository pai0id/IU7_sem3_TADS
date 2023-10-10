#!/bin/bash

in_file=$1
out_file=$2
prog="./app.exe"

res=$($prog < "$in_file")

rm tmp -f
touch tmp
echo "$res" >> tmp

if ! ./func_tests/scripts/comparator.sh tmp "$out_file"; then
    exit 0
else
    exit 1
fi
