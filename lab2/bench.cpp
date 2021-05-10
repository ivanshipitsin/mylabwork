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

int dynamictestget(){
    int * array;
    int p = 0;
    array = new int[10];
    for(int i = 0; i < 10; i++){
        array[i] = i;
    }
    DynamicArray<int> a(array, 10);
    try{
        std::cout << a.Get(0) << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
        p = -1;
    }

    try{
        std::cout << a.Get(10) << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
        p = -2;
    }

    try{
        std::cout << a.Get(-2) << std::endl;
    }catch(std::string s){
        std::cerr << s << std::endl;
        p = -3;
    }
    return p;
}


int main(int argc,  char ** argv){
    std::cout << "\\\\\\\\\\\\BENCHMAKER2000\\\\\\\\\\\\" << std::endl;
    dynamictestcreate();
    int p = dynamictestget();
    std:: cout << p << std::endl;
    return 0;
}