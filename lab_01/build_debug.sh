#!/bin/bash

for i in ./*.c ; do
    gcc -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -g3 -Wvla -O0 "$i"
done

gcc -o app.exe -g3 ./*.o -lm
