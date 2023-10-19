# WASM-RIPE: Runtime Intrusion Prevention Evaluator for WebAssembly
This repository provides an early version of WASM-RIPE, a tool for WebAssembly security benchmarking.

Since attacks on WebAssembly files are completely different from attacks on native C files, WASM-RIPE completely reconstructed the attacks of the existing [RIPE](https://github.com/johnwilander/RIPE) to create new attack codes.

Since this tool is still an early version, it has been implemented for only three attacks: stack overflow, indirect call redirection, and rodata constant overwrite.

## How to build and run
#### Build
To build the benchmark, you have to run 'build.sh' file with one argument.

```bash
./build.sh [none|ubsan|asan|clean]
```

If you run 'build.sh' file with 'none', 'ubsan', or 'asan' argument, it will compile the C code by Emscripten with sanitizer correspending to argument.

It will also attach the frontend code of `source/ripe_tester.js` to the generated js file.

If you run 'build.sh' file with 'clean' argument, it will delete all files generated during the compilation process.

The generated html file can be executed from the address `localhost:[port number]/wasm_attack.html` through the following command.

```bash
emrun --no_browser --port [port number] .
```

#### Individual test
To run a specific attack, you need to enter the following command on the web console.

```bash
callMain(["attack_type", "function_type"])
```

There are three types of `attack_type`: `stackoverflow`, `indirectcall`, `rodataoverwrite`.

There are three types of `function_type`: `strcpy`, `strncpy`, `memcpy`.

#### Full benchmark
All attacks for all attack types or specific attack types can be executed by entering the following commands on the web console.
This could be achieved by the `source/ripe_tester.js` file.

```bash
runTest("attack_type")
```
There are four types of `attack_type`: `all`, `stackoverflow`, `indirectcall`, `rodataoverwrite`.

#### How to see the result
You can observe the result of benchmark on the web console.
