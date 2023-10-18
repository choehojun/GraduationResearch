#!/bin/bash

sanitizer=$1

if [ ${sanitizer} == "none" ]; then
	emcc ./source/wasm_attack.c -o wasm_attack.html
elif [ ${sanitizer} == "ubsan" ]; then
	emcc ./source/wasm_attack.c -fsanitize=undefined -o wasm_attack.html
elif [ ${sanitizer} == "asan" ]; then
	emcc ./source/wasm_attack.c -fsanitize=address -o wasm_attack.html
elif [ ${sanitizer} == "clean" ]; then
	rm *wasm*
	exit 1
else
	echo "Please enter the type of sanitizer [none, ubsan, asan] or word \"clean\""
	exit 1
fi

cat ./source/ripe_tester.js wasm_attack.js > new_wasm_attack.js

sed -i "s/<script async type=\"text\/javascript\" src=\"wasm_attack.js\"><\/script>/<script async type=\"text\/javascript\" src=\"new_wasm_attack.js\"><\/script>/g" wasm_attack.html