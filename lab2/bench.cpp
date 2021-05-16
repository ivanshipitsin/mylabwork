//#define DEBUG

#include <iostream>
#include <fstream>
#include "list.hpp"
#include "dynamic.hpp"
#include "sequence.hpp"
#include "matrix.hpp"
#include "unit.hpp"


int dynamictestcreate(){ // test for debug memory error and memleak
    DynamicArray<int> a; // first construction
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
    int * massive = new int [100];
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            massive[i*10 + j] = i + j;
        }
    }
    Matrix<int> mat2(massive, 10);
    std::cout << mat2.GetDim() << " " << mat2.Get(5,6) << std::endl;
    delete [] massive;
    return 0;
}

int errortestcode(){
    LinkedListSequence<Matrix<double> > matdd;
    double * temp;
    int n = 0;
    std::cout << "Enter dimention:\n";
    std::cin >> n;
    std::cout << "Enter Matrix:\n";
    temp = read<double>(std::cin, n*n); 
    Matrix<double> newmatr(temp, n);
    matdd.Append(newmatr);
    scanf("%*c");
    clear<double>(temp, n);
    newmatr.clear();
    return 0;
}

int concatsequencetest(){
    std::ifstream in("test/concatsequence");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size1 = 0, size2 = 0, size3 = 0;
        in >> size1;
        int* data1, *data2, *data3;
        data1 = read<int>(in, size1);
        in >> size2;
        data2 = read<int>(in, size2);
        in >> size3;
        data3 = read<int>(in, size3);
        ArraySequence<int> a1(data1,size1);
        ArraySequence<int> a2(data2,size2);
        ArraySequence<int> * a3 = a1.Concat(&a2);
        std::cerr << "Concat in ArraySequence" << std::endl;
        comparedata<int>(a3, data3, size3);

        LinkedListSequence<int> l1(data1,size1);
        LinkedListSequence<int> l2(data2,size2);
        LinkedListSequence<int> * l3 = l1.Concat(&l2);
        std::cerr << "Concat in LinkedListSequence" << std::endl;
        comparedata<int>(l3, data3, size3);

        clear<int>(data1, size1);
        clear<int>(data2, size2);
        clear<int>(data3, size3);
    }
    return 0;
}

int subsequencetest(){
    std::ifstream in("test/subsequence");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size1 = 0, start = 0, end = 0;
        in >> size1;
        int* data1, *data2;
        data1 = read<int>(in, size1);
        in >> start >> end;
        data2 = read<int>(in, end - start + 1);
        ArraySequence<int> a1(data1, size1);
        ArraySequence<int> * a3 = a1.GetSubsequence(start, end);
        std::cerr << "SubSequence in ArraySequence" << std::endl;
        comparedata<int>(a3, data2, end - start + 1);

        LinkedListSequence<int> l1(data1,size1);
        LinkedListSequence<int> * l3 = l1.GetSubsequence(start, end);
        std::cerr << "SubSequence in LinkedListSequence" << std::endl;
        comparedata<int>(l3, data2, end - start + 1);

        clear<int>(data1, size1);
        clear<int>(data2, end - start + 1);
    }
    return 0;
}

int main(int argc,  char ** argv){
    std::cout << "\\\\\\\\\\\\BENCHMAKER2000\\\\\\\\\\\\" << std::endl;
    dynamictestcreate();
    dynamictestget();
    matrixtestcreat();
    //errortestcode();
    subsequencetest();
    concatsequencetest();
    return 0;
}