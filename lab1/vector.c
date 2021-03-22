#include "vector.h"

vector * makevector(int sizem) {
    vector * res = (vector *)calloc(1, sizeof (vector));
    res->size = sizem;
    return res;
}

int add(vector * v, void * data, int n) {
    int len = v->len;
    int size = v->size;
    v->head = realloc(v->head, (len + n) * size);
    memcpy(v->head + len * size, data, size * n);
    (v->len) += n;
    return 0;
}


void deletevector(vector * v) {
    if (v->head) {
        free(v->head);
    }
    free(v);
}