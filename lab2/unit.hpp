#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>
#include "Vector.hpp"

template<class T>
T * read(std::istream & in, int size){
    T * res = new T[size];
    for(int i = 0; i < size; i++) {
        in >> res[i];
    }
    #ifdef DEBUG 
        std::cerr << "Read Object type T**" << res << " " << size << std::endl;
    #endif
    return res;
}


template<class T>
void clear(T* masivblackhole, int size){
    #ifdef DEBUG 
        std::cerr << "Destroy Object type T**" << masivblackhole << " " << size <<std::endl;
    #endif
    
    delete [] masivblackhole;
}


template<class T>
int comparedata(Sequence<T> * ptr, T* data, int count){
    try{
        for(int i = 0; i < count ; i++){
            if(ptr->Get(i) != data[i]){
                std::cerr << "error in :" << ptr->Get(i) << "!=" << data[i] << std::endl;
            }
        }
    }catch(const char * s){
        std::cerr << s << std::endl;
        return -1;
    }
    return 0;
}

template<class T>
int comparedatav(Vector<T> * ptr, T* data, int count){
    try{
        for(int i = 0; i < count ; i++){
            if(std::abs(ptr->Get(i) - data[i])>0.00001){
                std::cerr << "error in :" << ptr->Get(i) << "!=" << data[i] << std::endl;
            }
        }
    }catch(const char * s){
        std::cerr << s << std::endl;
        return -1;
    }
    return 0;
}

template<class T>
int comparedatam(Matrix<T> * ptr, T* data, int count){
    try{
        for(int i = 0; i < count*count ; i++){
            if(std::abs(ptr->Get(i / count, i % count) - data[i])> 0.0001){
                std::cerr << "error in :" << ptr->Get(i / count , i % count) << "!=" << data[i] << std::endl;
            }
        }
    }catch(const char * s){
        std::cerr << s << std::endl;
        return -1;
    }
    return 0;
}

#endif