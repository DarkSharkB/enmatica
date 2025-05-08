## enma library has the following dependencies
 - googletest

## To Build a Library:
    
    clang++ -DDEBUG -mavx2 -mfma -c -g -O2 ../../include/*.cpp

    llvm-ar -rc lib/enma.lib build/temp/*.o

## To Compile Test (Direct Compilation):

    clang++ -DDEBUG -std=c++17 -mavx2 -mfma -O2 -g -I../../include/ -I../../external/ -L../lib/ ../../test/main.cpp -o test.exe -lgtest