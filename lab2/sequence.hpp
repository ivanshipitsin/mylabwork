#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP 1
#include "list.hpp"
#include "dynamic.hpp"


template<class T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int) const = 0;
    virtual Sequence<T>* GetSubsequence(int,int) = 0;
    virtual int GetLenght() const = 0;
    virtual void Append(const T&) = 0;
    virtual void Prepend(const T&) = 0;
    virtual void Set(int,const T&) = 0;
    virtual void InsertAt(const T&, int) = 0;
    virtual Sequence<T> * Concat(Sequence <T> *) = 0;
};

template <class T>
class ArraySequence : public Sequence<T>{
public:
    ArraySequence(T*,int);
    ArraySequence();
    ArraySequence(const ArraySequence<T> &);
    ArraySequence(int);
    ~ArraySequence();
    T GetFirst() const;
    T GetLast() const;
    T Get(int) const;
    void Set(int,const T&);
    ArraySequence<T>* GetSubsequence(int,int);
    int GetLenght() const;
    void Append(const T&);
    void Prepend(const T&);
    void InsertAt(const T&, int);
    ArraySequence<T> * Concat(Sequence <T> *);
    //friend void clear();

private:
    DynamicArray<T>* mass;
};

template <class T>
class LinkedListSequence : public Sequence<T>{
public:
    LinkedListSequence(T*,int);
    LinkedListSequence();
    LinkedListSequence(const LinkedListSequence<T> &);
    ~LinkedListSequence();
    T GetFirst() const;
    T GetLast() const;
    T Get(int) const;
    void Set(int,const T&);
    LinkedListSequence<T>* GetSubsequence(int,int);
    int GetLenght() const;
    void Append(const T&);
    void Prepend(const T&);
    void InsertAt(const T&, int);
    LinkedListSequence<T> * Concat(Sequence <T> *);
    //friend void clear();
private:
    LinkedList<T>*  mass;
};



template<class T>
LinkedListSequence<T>::LinkedListSequence(T* item,int count){
    mass = new LinkedList<T>(item, count);
}

template<class T>
LinkedListSequence<T>::LinkedListSequence(){
    mass = new LinkedList<T>();
}

template<class T>
LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence <T> & list) {
    mass = new LinkedList<T>(*(list.mass));
}

template<class T>
LinkedListSequence<T>::~LinkedListSequence(){
    #ifdef DEBUG 
        std::cerr << "Destroy Object type LinkedListSequence<T>" << mass << std::endl;
    #endif
    
    delete mass;

}

template<class T>
T LinkedListSequence<T>::GetFirst() const{
    return mass->GetFirst();
}

template<class T>
T LinkedListSequence<T>::GetLast() const{
    return mass->GetLast();
}

template<class T>
T LinkedListSequence<T>::Get(int ind) const{
    return (mass->Get(ind));
}

template<class T>
void LinkedListSequence<T>::Set(int ind,const T& item){
    mass->Set(ind, item);
}

template<class T>
int LinkedListSequence<T>::GetLenght() const{
    return mass->GetLenght();
}

template<class T>
LinkedListSequence<T> * LinkedListSequence<T>::GetSubsequence(int start,int stop){
    LinkedListSequence<T> * newlist = new LinkedListSequence();
    newlist->mass = mass->GetSubList(start, stop);
    return newlist;
}

template<class T>
void LinkedListSequence<T>::Append(const T& item){
    mass->Append(item);
}

template<class T>
void LinkedListSequence<T>::Prepend(const T& item){
    mass->Prepend(item);
}

template<class T>
void LinkedListSequence<T>::InsertAt(const T& item, int ind){
    mass->InsertAt(item, ind);
}

template<class T>
LinkedListSequence<T> * LinkedListSequence<T>::Concat(Sequence <T> * list){
    for(int i = 0; i < list->GetLenght(); i++) {
        Append(list->Get(i));
    }

    return this;
}


/// ArraySequence
template<class T>
ArraySequence<T>::ArraySequence(T* item,int count){
    mass = new DynamicArray<T>(item, count);

    #ifdef DEBUG 
        std::cerr << "Generate Object type ArraySequence<T> with construct (T*, size)" << mass << " " << count << std::endl;
        std::cerr << "Type of T" << typeid(mass->Get(0)).name() <<std::endl;
    #endif
}

template<class T>
ArraySequence<T>::ArraySequence(int count){
    mass = new DynamicArray<T>(count);

    #ifdef DEBUG 
        std::cerr << "Generate Object type ArraySequence<T> with construct (size)" << mass << " " << count << std::endl;
        std::cerr << "Type of T" << typeid(mass->Get(0)).name() <<std::endl;
    #endif
}

template<class T>
ArraySequence<T>::ArraySequence(){
    mass = new DynamicArray<T>();

    #ifdef DEBUG 
        std::cerr << "Generate Object type ArraySequence<T> with construct ()" << mass << std::endl;
        std::cerr << "Type of T" << typeid(mass->Get(0)).name() <<std::endl;
    #endif
}

template<class T>
ArraySequence<T>::ArraySequence(const ArraySequence <T> & list){


    mass = new DynamicArray<T>(*(list.mass));
}

template<class T>
ArraySequence<T>::~ArraySequence(){

    #ifdef DEBUG 
        std::cerr << "Destroy Object type ArraySequence<T>" << mass << std::endl;
    #endif

    delete mass;
}

template<class T>
T ArraySequence<T>::GetFirst() const {
    return mass->Get(0);
}

template<class T>
T ArraySequence<T>::GetLast() const {
    return mass->Get(mass->GetSize() - 1);
}

template<class T>
T ArraySequence<T>::Get(int ind) const{
    return (mass->Get(ind));
}

template<class T>
void ArraySequence<T>::Set(int ind,const T& item){
    mass->Set(ind, item);
}

template<class T>
int ArraySequence<T>::GetLenght() const{
    return mass->GetSize();
}

template<class T>
ArraySequence<T> * ArraySequence<T>::GetSubsequence(int start,int stop){
    ArraySequence<T> * newlist = new ArraySequence<T>();
    newlist->mass = (mass->Getsubarray(start, stop));
    return newlist;
}

template<class T>
void ArraySequence<T>::Append(const T& item){
    mass->Resize(mass->GetSize() + 1);
    mass->Set(mass->GetSize() - 1, item);
}

template<class T>
void ArraySequence<T>::Prepend(const T& item){
    mass->Prepend(item);
}

template<class T>
void ArraySequence<T>::InsertAt(const T& item, int ind){
    mass->InsertAt(ind, item);
}

template<class T>
ArraySequence<T> * ArraySequence<T>::Concat(Sequence <T> * list){
    for(int i = 0; i < list->GetLenght(); i++) {
        Append(list->Get(i));
    }

    return this;
}
#endif