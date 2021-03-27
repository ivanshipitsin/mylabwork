#include "vector.h"

vector * makevector(int sizem) {
    vector * res = (vector *)calloc(1, sizeof (vector));

    if (!res) {
        return NULL;
    }

    if (sizem > 0) {
        res->size = sizem;
        return res;
    } else {
        return NULL;
    }
}

int add(vector * v, void * data, int n) {
    int len = v->len;
    int size = v->size;
    v->head = realloc(v->head, (len + n) * size);
    if (!v->head) {
        return -1;
    }
    void * ptr;
    ptr = memcpy(v->head + len * size, data, size * n);
    if (!ptr) {
        return -2;
    }
    (v->len) += n;
    return 0;
}


void deletevector(vector * v) {
    if (v->head) {
        free(v->head);
    }
    free(v);
}