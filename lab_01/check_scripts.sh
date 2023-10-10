#!/bin/bash

for i in ./*.sh ./func_tests/scripts/*.sh ; do
    shellcheck "$i"
done
