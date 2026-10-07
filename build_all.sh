#!/usr/bin/env bash
set -eu

cd "$(dirname "$0")"
mkdir -p .build

for lab in {1..11}; do
    for source in "${lab}lab"/task*.cpp; do
        name=$(basename "$source" .cpp)
        g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 "$source" -o ".build/${lab}lab_${name}"
        echo "Готово: ${lab}lab/$name"
    done
done
