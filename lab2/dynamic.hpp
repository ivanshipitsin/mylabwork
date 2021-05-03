#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP 1

#include <memory.h>
#include <stdlib.h>
#include <algorithm>

template<class T>
class DynamicArray {
public:
    DynamicArray(T*, int);
    DynamicArray(int);
    DynamicArray();
    DynamicArray(const DynamicArray<T> &);
    ~DynamicArray();
    T Get(int);
    int GetSize();
    void Set(int,T);
    void Resize(int);
    void Prepend(T item);
    void InsertAt(int, T);
    DynamicArray<T> * Concat(DynamicArray<T> *);
    DynamicArray<T> * Getsubarray(int, int);
private:
    T* mass;
    int len;
    int cap;
};


template<class T>
DynamicArray<T>::DynamicArray(T* item,int count){
    if(item == nullptr) {
        mass = nullptr;
        len = 0;
        cap = 0;
    }else {
        mass = new T[count];
        len = count;
        cap = count;
        memcpy(mass, item, count);
    }
}

template<class T>
DynamicArray<T>::DynamicArray(){
    mass = nullptr;
    len = 0;
    cap = 0;
}

template<class T>
DynamicArray<T>::DynamicArray(int size){
    if(size == 0) {
        throw "Not array creative";
    }
    mass = new T[size];
    len = size;
    cap = size;
}

template<class T>
DynamicArray<T>::~DynamicArray(){
    delete[] (mass);
}
template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &arr){
    mass = new T[arr.cap];
    cap = arr.cap;
    len = arr.len;
    memcpy(mass, arr.mass, len);
}

template<class T>
T DynamicArray<T>::Get(int ind){
    if(ind >= len){
        throw "IndexOutOfRange";
    }
    return mass[ind];
}

template<class T>
int DynamicArray<T>::GetSize(){
    return len;
}

template<class T>
void DynamicArray<T>::Set(int ind, T item) {
    if(ind >= len){
        throw "IndexOutOfRange";
    }
    mass[ind] = item;
}

template<class T>
void DynamicArray<T>::Resize(int newSize) {
    if(len == 0){
        int size = newSize;
        mass = new T[size];
        cap = size;
    }else if(newSize > cap) {
        int size = std::max<int>(2 * len, newSize);
        T* newdata = new T[size];
        memcpy(newdata, mass, len * sizeof(T));
        delete [] mass;
        mass = newdata;
        cap = size;
    }
    len = newSize;
}
template<class T>
void DynamicArray<T>::Prepend(T item) {
    if(GetSize() == 0) {
        Resize(1);
        mass[0] = item;
    } else {
        Resize(GetSize() + 1);
        memmove(mass + 1, mass, (len - 1) * sizeof(T));
        mass[0] = item;
    }
}

template<class T>
void DynamicArray<T>::InsertAt(int ind,T item) {
    if(ind == GetSize()) {
        Resize(GetSize() + 1);
        Set(GetSize() - 1, item);
    } else if (ind > GetSize()){
        throw "IndexOutOfRange";
    }else {
        Resize(GetSize() + 1);
        memmove(mass + ind + 1, mass + ind, (GetSize() - ind - 1) * sizeof(T));
        Set(ind, item);
    }
}
template<class T>
DynamicArray<T> * DynamicArray<T>::Concat(DynamicArray<T> * list){
    Resize(GetSize() + list->GetSize());
    memcpy(mass + GetSize(), list->mass, list->GetSize() * sizeof(T));
    return this;
}
template<class T>
DynamicArray<T> * DynamicArray<T>::Getsubarray(int start , int end){
    if(start < 0 or start >= len or end >= len or end < 0 or start > end) {
        throw "IndexOutOfRange";
        return nullptr;
    }
    DynamicArray<T> * res = new DynamicArray<T>();
    res->mass = mass + start;
    res-> len = end - start + 1;
    return res;

}

#endif