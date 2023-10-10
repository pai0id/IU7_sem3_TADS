#!/bin/bash

BLUE=$'\e[1;34m'
GREEN=$'\e[1;32m'
RED=$'\e[1;31m'
NC=$'\e[1;0m'
n_err=0

echo "$BLUE checking scripts: $NC"
echo
./check_scripts.sh
echo
echo "$BLUE build debug: $NC"
echo
./build_debug.sh
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
./clean.sh
echo
echo "$BLUE build /w address sanitizer: $NC"
echo
./build_debug_asan.sh
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
./clean.sh
echo
echo "$BLUE build /w memory sanitizer: $NC"
echo
./build_debug_msan.sh
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
./clean.sh
echo
echo "$BLUE build /w undefined behavior sanitizer: $NC"
echo
./build_debug_ubsan.sh
if ./func_tests/scripts/func_tests.sh; then
    echo "$GREEN GOOD $NC"
else
    echo "$RED BAD $NC"
    n_err=$((n_err+1))
fi
./clean.sh
echo
echo "$BLUE build /w gcov: $NC"
./build_debug_gcov.sh
./collect_coverage.sh
./clean.sh
echo
if [ $n_err != 0 ]; then
    echo " $RED ERROR OCCURED $NC"
else
    echo "$GREEN ALL GOOD $NC"
fi

exit $n_err
