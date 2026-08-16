# Enmatica
## High Performant, Lightweight Mathematics Library
Enmatica or enma (for short) is a lightweight, header-only C++ mathematics library designed for performing calculations involved in computer graphics and simulation.

Includes vectors, matrices and quaternions types with swizzling support along with SIMD acceleration for all possible operations.

## Dependencies
The following dependencies are required to build and run the tests,
 - googletest

## Build Process
### Usage In Your Project
 - Copy the `include` folder to your dependencies location
 - Include the `enma.hpp` in required source files and compile directly.

### Test Executable Generation
#### Debug
```
clang++ -std=c++17 -Wall -mavx2 -mfma -g -DDEBUG -Iinclude/ -Iexternal/googletest/include/ -Lexternal/googletest/lib/ test/main.cpp test/sfvec.cpp -o build/debug/bin/test.exe -lgtest
```

#### Release
```
clang++ -std=c++17 -Wall -mavx2 -mfma -O2 -Iinclude/ -Iexternal/googletest/include/ -Lexternal/googletest/lib/ test/main.cpp test/sfvec.cpp -o build/release/bin/test.exe -lgtest
```