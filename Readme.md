Enmatica is a lightweight, header-only C++ math library designed for high-performance game development. It includes core math types (vectors, matrices, quaternions) with SIMD support, swizzling, and transform operations. Built without CMake for easy integration, it's actively used in my gameplay and engine projects.

## enma library has the following dependencies
 - googletest

## To Build a Library:
    
    clang++ -DDEBUG -mavx2 -mfma -c -g -O2 ../../include/*.cpp

    llvm-ar -rc lib/enma.lib build/temp/*.o

## To Compile Test (Direct Compilation):

    clang++ -DDEBUG -std=c++17 -mavx2 -mfma -O2 -g -I../../include/ -I../../external/ -L../lib/ ../../test/main.cpp -o test.exe -lgtest
