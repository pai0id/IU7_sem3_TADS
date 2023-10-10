#!/bin/bash

in_file=$1
prog="./app.exe"

rm tmp -f
touch tmp

if ! $prog < "$in_file" > tmp; then
    exit 0
else
    exit 1
fi
