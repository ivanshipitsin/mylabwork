#ifndef Vector_HPP 
#define Vector_HPP 1

#include "sequence.hpp"
#include <complex>
#include <math.h>

template<class T>
class Vector{
public:
    Vector(){
        vec = nullptr;
    }
    Vector(int count){
        vec = new ArraySequence<T>(count);
    }
    Vector(T* items, int count){
        vec = new ArraySequence<T>(items, count);
    }
    Vector(const Vector<T> & copy){
        vec = new ArraySequence<T>(*(copy.vec));
    }
    T Get(int index) const{
        return vec->Get(index);
    }
    void Set(int index, const T& obj){
        vec->Set(index, obj);
    }
    Vector<T> * sum(const Vector<T> & a){
        if(a.GetDim() != GetDim()){
            throw "Error size of vector";
        }
        Vector<T> * res = new Vector(GetDim());
        for(int i = 0; i < GetDim(); i++){
            res->Set(i, Get(i) + a.Get(i));
        }
        return res;
    }
    Vector<T> * scalar(const T& num){
        Vector<T> * res = new Vector(GetDim());
        for(int i = 0; i < GetDim(); i++){
            res->Set(i, Get(i) * num);
        }
        return res;
    }
    std::complex<double> dot(const Vector<T>& a){
        std::complex<double> num = 0;
        if(a.GetDim() == GetDim()){
            for(int i = 0; i < GetDim(); i++){
                num += Get(i) * std::conj(a.Get(i));
            }
        }
        return num;
    }

    double norm(){
        return std::sqrt(std::real(dot(*this)));
    }
    int GetDim() const{
        return vec->GetLenght();
    }
    void clear(){
        delete vec;
    }
private:
        ArraySequence<T> * vec;  
};

#endif