#!/bin/bash

./func_tests/scripts/func_tests_silent.sh

echo
echo "Result:"
echo
for i in ./*.c ; do
    gcov "$i"
    echo
done
