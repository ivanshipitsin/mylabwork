#include "utilit.h"


double complex * readc(FILE * f, int n) {
    double complex *a = (double complex *)calloc(n, sizeof(double complex));
    for (int i = 0; i < n; i++) {
        double im, re;
        fscanf(f, "%lf %lf", &re, &im);
        __real__ a[i] = re;
        __imag__ a[i] = im;
    }
    return a;
}


double * read(FILE * f, int n) {
    double *a = (double *)calloc(n, sizeof(double));
    if (!a) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        if(!fscanf(f, "%lf", a + i)) {
            if(!a) {
                return NULL;
            } else {
                free(a);
                return NULL;
            }
        }
    }
    return a;
}