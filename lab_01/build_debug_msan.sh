#!/bin/bash

for i in ./*.c ; do
    clang -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer -g3 -Wvla -O0 "$i"
done

clang -o app.exe -g3 ./*.o -lm -fsanitize=memory
