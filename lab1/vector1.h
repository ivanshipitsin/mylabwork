#ifndef VECTRO_H_
#define VECTRO_H_

#include <stdlib.h>
#include <string.h>

typedef struct Vector {
    void * head;
    int len;
    int * sizes;
} vector;

vector * makevector();
int add(vector *, void *, int);
void deletevector(vector *);


#endif