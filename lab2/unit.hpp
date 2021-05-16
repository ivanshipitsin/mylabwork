#ifndef UNIT_HPP
#define UNIT_HPP
#include <iostream>


template<class T>
T * read(std::istream & in, int size){
    T * res = new T[size * size];
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            std::cin >> res[i*size + j];
        }
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


#endif