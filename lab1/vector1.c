#include "vector1.h"

vector * makevector() {
    return (vector *)calloc(1,sizeof (vector));
}

int add(vector * v, void * data, int size) {
    int len = v->len;
    if(!v->head) {
        v->head = malloc(size);
        v->len = 1;
        v->sizes = (int *)calloc(1, sizeof(int));
        v->sizes[0] = size;
        memcpy(v->head, data, size);
    } else {
        v->head = realloc(v->head, v->sizes[len-1] + size);
        (v->len)++;
        v->sizes = (int *)realloc(v->sizes, len);
        v->sizes[len-1] = v->sizes[len - 2] + size;
        memcpy(v->head + v->sizes[len - 2], data, size);
    }
}


void deletevector(vector * v) {
    if (v->head) {
        free(v->head);
        free(v->sizes);
    }
    free(v);
}