#!/bin/bash

file1=$1
file2=$2
verb=$3

if [ -z "$file1" ] || [ -z "$file2" ] || [ ! -f "$file1" ] || [ ! -f "$file2"  ]; then
    if [[ $verb == "-v" ]]; then
        echo "Please enter correct file names"
    fi
    exit 2
elif [ ! -r "$file1" ] || [ ! -r "$file2"  ]; then
    if [[ $verb == "-v" ]]; then
        echo "Permission error"
    fi
    exit 3
fi

string="Res: "

# Ищем первое вхождение строки "Result: " в обоих файлах
index1=$(grep -m 1 -b -o "$string" "$file1" | cut -d ':' -f 1)
index2=$(grep -m 1 -b -o "$string" "$file2" | cut -d ':' -f 1)

# Сравниваем текст после первого вхождения строки "Result: "
if [ "$(tail -c +$((index1+${#string}+1)) "$file1" | md5sum)" == "$(tail -c +$((index2+${#string}+1)) "$file2" | md5sum)" ]; then
  if [ "$verb" == "-v" ]; then
        echo "files match"
    fi
    exit 0
else
  if [ "$verb" == "-v" ]; then
        echo "files do not match"
    fi
    exit 1
fi
