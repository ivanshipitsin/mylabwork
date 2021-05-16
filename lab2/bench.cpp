#define DEBUG

#include <iostream>
#include "list.hpp"
#include "dynamic.hpp"
#include "sequence.hpp"
#include "matrix.hpp"
#include "unit.hpp"


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
    return 0;
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
    }catch(char const * s){
        std::cerr << s << std::endl;
        p = -1;
    }

    /*try{
        std::cout << a.Get(10) << std::endl;
    }catch(char const * s){
        std::cerr << s << std::endl;
        p = -2;
    }

    try{
        std::cout << a.Get(-2) << std::endl;
    }catch(char const * s){
        std::cerr << s << std::endl;
        p = -3;
    }*/
    delete[] array;
    return p;
}

int matrixtestcreat(){
    Matrix<int> mat;
    std::cout << mat.GetDim() << std::endl;
    Matrix<int> mat1(10);
    std::cout << mat1.GetDim() << std::endl;
    int ** massive = new int *[10];
    for (int i = 0; i < 10; i++){
        massive[i] = new int [10];
        for(int j = 0; j < 10; j++){
            massive[i][j] = i + j;
        }
    }
    Matrix<int> mat2(massive, 10);
    std::cout << mat2.GetDim() << " " << mat2.Get(5,6) << std::endl;
    for(int i = 0; i < 10; i++){
        delete[] massive[i];
    }
    delete [] massive;
    return 0;
}

int errortestcode(){
    ArraySequence<Matrix<double>> matdd;
    double ** temp;
    int n = 0;
    std::cout << "Enter dimention:\n";
    std::cin >> n;
    std::cout << "Enter Matrix:\n";
    temp = read<double>(std::cin, n); 
    Matrix<double> newmatr(temp, n);
    matdd.Append(newmatr);
    scanf("%*c");
    clear<double>(temp, n);
    return 0;
}

int main(int argc,  char ** argv){
    std::cout << "\\\\\\\\\\\\BENCHMAKER2000\\\\\\\\\\\\" << std::endl;
    dynamictestcreate();
    dynamictestget();
    matrixtestcreat();
    errortestcode();
    return 0;
}