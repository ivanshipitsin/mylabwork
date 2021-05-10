#include <iostream>
#include "list.hpp"
#include "dynamic.hpp"
#include "sequence.hpp"
#include "matrix.hpp"

int dynamictestcreate(){ // test for debug memory error and memleak
    DynamicArray<int> a(); // first construction
    DynamicArray<int> b(10); // second
    int * array;
    array = new int[10];
    for(int i = 0;i < 10;i++){
        array[i] = i;
    }
    DynamicArray<int> c(array, 10); // firdth
    DynamicArray<int> d = c; // copy
    delete[] array;
}


int main(int argc,  char ** argv){
    std::cout << "\\\\\\\\\\\\BENCHMAKER2000\\\\\\\\\\\\" << std::endl;
    dynamictestcreate();
    return 0;
}