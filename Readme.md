## To Build a Library:
    
    clang++ -DDEBUG -mavx2 -c -O2 ../include/*.cpp -g

    llvm-ar -rc lib/enma.lib build/*.o

## To Compile Directly (Example - See test Folder):

    clang++ -DDEBUG -std=c++17 -mavx2 -O2 -I../include ../test/main.cpp -o test.exe -g