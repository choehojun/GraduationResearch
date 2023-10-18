#!/bin/bash

sanitizer=$1

if [ ${sanitizer} == "none" ]; then
	emcc ./source/wasm_attack.c -o wasm_attack.html
elif [ ${sanitizer} == "ubsan" ]; then
	emcc ./source/wasm_attack.c -fsanitize=undefined -o wasm_attack.html
elif [ ${sanitizer} == "asan" ]; then
	emcc ./source/wasm_attack.c -fsanitize=address -o wasm_attack.html
else
	echo "Please enter the type of sanitizer [none, ubsan, asan]"
	exit 1
fi
