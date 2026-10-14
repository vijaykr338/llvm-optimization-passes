#!/bin/bash

if [ -d "build" ]; then
    rm -rf build
fi

mkdir build && cd build

export LDFLAGS="-L/opt/homebrew/opt/llvm/lib/clang/19 -L/opt/homebrew/opt/llvm/lib/c++ -L/opt/homebrew/opt/llvm/lib/unwind -lunwind"
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

cmake ../ -DCMAKE_C_COMPILER=/opt/homebrew/opt/llvm/bin/clang -DCMAKE_CXX_COMPILER=/opt/homebrew/opt/llvm/bin/clang++ -DCMAKE_CXX_FLAGS="-fno-rtti" -DCMAKE_SYSTEM_NAME=Darwin -DLLVM_BIN_DIR=/opt/homebrew/opt/llvm/bin
make

cd ..