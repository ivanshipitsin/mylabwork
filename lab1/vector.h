#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdlib.h>
#include <string.h>

typedef struct Vector {
    void * head;
    int len;
    int size;
} vector;

vector * makevector(int);
int add(vector *, void *, int);
void deletevector(vector *);


#endif