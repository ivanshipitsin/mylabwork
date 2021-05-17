//#define DEBUG

#include <iostream>
#include <fstream>
#include "list.hpp"
#include "dynamic.hpp"
#include "sequence.hpp"
#include "matrix.hpp"
#include "unit.hpp"
#include "Vector.hpp"

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

int vectestsum(){
    std::ifstream in("test/vecsum");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size = 0;
        in >> size;
        int* data1, *data2, *data3;
        data1 = read<int>(in, size);
        data2 = read<int>(in, size);
        data3 = read<int>(in, size);
        Vector<int> v1(data1, size);
        Vector<int> v2(data2, size);
        Vector<int> * v3 = v1.sum(v2);
        std::cerr << "VectorSum test:" << std::endl;
        comparedatav<int>(v3, data3, size);

        clear<int>(data1, size);
        clear<int>(data2, size);
        clear<int>(data3, size);
        v1.clear();
        v2.clear();
        v3->clear();
        delete v3;
    }
    return 0;
}

int vectestscalar(){
    std::ifstream in("test/vecscalar");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN VECTESTSCALAR" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size = 0, scal = 0;
        in >> size;
        int* data1, *data2;
        data1 = read<int>(in, size);
        in >> scal;
        data2 = read<int>(in, size);
        Vector<int> v1(data1, size);
        Vector<int> * v3 = v1.scalar(scal);
        std::cerr << "VectorScalar test:" << std::endl;
        comparedatav<int>(v3, data2, size);
        
        clear<int>(data1, size);
        clear<int>(data2, size);
        v3->clear();
        delete v3;
        v1.clear();
    }
    return 0;
}

int vectestnorm(){
    std::ifstream in("test/vecnorm");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size = 0;
        double res = 0;
        in >> size;
        double* data1;
        data1 = read<double>(in, size);
        in >> res;
        Vector<double> v1(data1, size);
        double maybe = v1.norm();
        std::cerr << "VectorNorm test:" << std::endl;
        if(std::abs(maybe - res) > 0.00001){
            std::cerr << "Error in VectorNorm test" << std::endl;
        }
        
        clear<double>(data1, size);
        v1.clear();
    }
    return 0;
}


int mattestsum(){
    std::ifstream in("test/matsum");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size = 0;
        in >> size;
        int* data1, *data2, *data3;
        data1 = read<int>(in, size*size);
        data2 = read<int>(in, size*size);
        data3 = read<int>(in, size*size);
        Matrix<int> v1(data1, size);
        Matrix<int> v2(data2, size);
        Matrix<int> * v3 = v1.Sum(v2);
        std::cerr << "MatrixSum test:" << std::endl;
        comparedatam<int>(v3, data3, size);

        clear<int>(data1, size);
        clear<int>(data2, size);
        clear<int>(data3, size);
        v1.clear();
        v2.clear();
        v3->clear();
        delete v3;
    }
    return 0;
}

int mattestnorm(){
    std::ifstream in("test/matnorm");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size = 0;
        double res = 0;
        in >> size;
        double* data1;
        data1 = read<double>(in, size*size);
        in >> res;
        Matrix<double> v1(data1, size);
        double maybe = v1.norm();
        std::cerr << "MatrixNorm test:" << std::endl;
        if(std::abs(maybe - res) > 0.00001){
            std::cerr << "Error in VectorNorm test" << std::endl;
        }
        
        clear<double>(data1, size);
        v1.clear();
    }
    return 0;
}

int mattestscalar(){
    std::ifstream in("test/matscalar");
    if(!in.is_open()){
        std::cerr << "FILE NOT OPEN VECTESTSCALAR" << std::endl;
        return -2;
    }
    int count = 0;
    in >> count;
    for(int n = 0; n < count; n++){
        int size = 0, scal = 0;
        in >> size;
        int* data1, *data2;
        data1 = read<int>(in, size*size);
        in >> scal;
        data2 = read<int>(in, size*size);
        Matrix<int> v1(data1, size);
        Matrix<int> * v3 = v1.Scalar(scal);
        std::cerr << "MatrixScalar test:" << std::endl;
        comparedatam<int>(v3, data2, size);
        
        clear<int>(data1, size);
        clear<int>(data2, size);
        v3->clear();
        delete v3;
        v1.clear();
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
    vectestnorm();
    vectestscalar();
    vectestsum();
    mattestsum();
    mattestnorm();
    mattestscalar();
    return 0;
}