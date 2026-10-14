# LLVM Custom Optimization Passes

An out-of-tree collection of LLVM optimization and analysis passes built with
the modern **New Pass Manager (NPM)**.

This project was built by **Vijay Kumar, DTU '27**, as part of a compiler course.

## Overview

The project demonstrates how to develop, build, register, and run LLVM pass
plugins without modifying the LLVM source tree. It includes small utility and
analysis passes as well as lightweight examples of common transformations.

### Highlights

- Built for LLVM 19 and later.
- Uses the New Pass Manager.
- Compiles as shared-library pass plugins.
- Supports out-of-tree CMake builds.
- Includes analysis, printer, and transformation passes.

## Requirements

- LLVM 19 or later
- CMake 3.20 or later
- A C++17-compatible compiler
- Make, Ninja, or another supported build tool

LLVM must be installed with its CMake package files available. If LLVM is
installed in a non-standard location, set `LLVM_DIR` to the directory
containing `LLVMConfig.cmake`.

For installation guidance, see the
[LLVM Getting Started documentation](https://llvm.org/docs/GettingStarted.html).

## Building

### Using the build script

The repository includes `build.sh` for a Homebrew-based LLVM installation on
macOS:

```sh
./build.sh
```

The script creates the build directory, configures CMake, and builds the pass
plugins. Update the LLVM paths in the script if LLVM is installed elsewhere.

### Manual build

From the project root, configure and build the project with CMake:

```sh
cmake -S . -B build \
  -DLLVM_DIR=/path/to/llvm/lib/cmake/llvm \
  -DCMAKE_CXX_COMPILER=/path/to/llvm/bin/clang++
cmake --build build
```

If the compiler is already on `PATH`, the compiler option can be omitted:

```sh
cmake -S . -B build -DLLVM_DIR=/path/to/llvm/lib/cmake/llvm
cmake --build build
```

The resulting shared libraries are written to `build/lib/`. On macOS they
typically use the `.dylib` extension; on Linux they typically use `.so`.

## Included Passes

| Pass | Shared library | Registered pipeline name | Level and kind |
| --- | --- | --- | --- |
| HelloWorld | `libHelloWorld` | `hello-world` | Module utility |
| OpcodeCounter | `libOpcodeCounter` | `print<opcode-counter>` | Function analysis and printer |
| ArithmeticSimplifier | `libArithmeticSimplifier` | `arithmetic-simplifier` | Function transformation |
| CFG Printer | `libCFGPrinter` | `cfg-printer` | Module analysis and printer |
| Function Call Counter | `libFunctionCallCounter` | `print<call-counter>` | Module analysis and printer |
| Instruction Replacer | `libInstructionReplacer` | `inst-replace` | Function transformation |
| Constant Propagation | `libConstantPropagation` | `constant-propagation` | Function transformation |
| Dead Code Elimination | `libDeadCodeElimination` | `dead-code-elimination` | Function transformation |

## Running the Passes

Generate LLVM IR from one of the example C inputs before running a pass. Using
`-O0` leaves the input unoptimized so that the custom passes have instructions
to process:

```sh
clang -O0 -S -emit-llvm inputs/hello.c -o hello.ll
```

The commands below use Linux-style plugin names. On macOS, use the corresponding
`.dylib` file name. Analysis and printer passes write their results to the
terminal, while transformation passes write transformed IR when an output file
is specified.

### HelloWorld

Prints a greeting when the module pass runs.

```sh
opt -load-pass-plugin ./build/lib/libHelloWorld.so \
  -passes="hello-world" -S hello.ll -o /dev/null
```

### OpcodeCounter

Counts instruction opcodes in each function and prints the analysis results.

```sh
opt -load-pass-plugin ./build/lib/libOpcodeCounter.so \
  -passes="print<opcode-counter>" -S hello.ll -o /dev/null
```

### ArithmeticSimplifier

Applies simple algebraic simplifications such as `x * 1 -> x` and
`x + 0 -> x`.

```sh
opt -load-pass-plugin ./build/lib/libArithmeticSimplifier.so \
  -passes="arithmetic-simplifier" -S hello.ll -o simplified.ll
```

### CFG Printer

Prints each function's control-flow graph in DOT format.

```sh
opt -load-pass-plugin ./build/lib/libCFGPrinter.so \
  -passes="cfg-printer" -S hello.ll -o /dev/null
```

### Function Call Counter

Counts direct calls to functions in the module and prints the results.

```sh
opt -load-pass-plugin ./build/lib/libFunctionCallCounter.so \
  -passes="print<call-counter>" -S hello.ll -o /dev/null
```

### Instruction Replacer

Replaces `add` instructions whose operands are identical with `sub`
instructions. This pass is intended to demonstrate instruction replacement and
is not generally semantics-preserving.

```sh
opt -load-pass-plugin ./build/lib/libInstructionReplacer.so \
  -passes="inst-replace" -S hello.ll -o replaced.ll
```

### Constant Propagation

Performs simple constant folding for binary operations, such as replacing
`add i32 5, 3` with the corresponding constant result.

```sh
opt -load-pass-plugin ./build/lib/libConstantPropagation.so \
  -passes="constant-propagation" -S hello.ll -o constant-propagated.ll
```

### Dead Code Elimination

Removes instructions that have no users and no side effects.

```sh
opt -load-pass-plugin ./build/lib/libDeadCodeElimination.so \
  -passes="dead-code-elimination" -S hello.ll -o dce.ll
```

## Repository Layout

```text
.
|-- include/     Pass headers
|-- inputs/      Example C and LLVM IR inputs
|-- lib/         Pass implementations and library build definitions
|-- build.sh     Convenience build script
`-- CMakeLists.txt
```

## Notes

- The transformation passes are educational examples and are intentionally
  lightweight.
- Passes that change IR may invalidate previously computed analyses.
- Use the `opt` executable from the same LLVM installation used to build the
  plugins.
