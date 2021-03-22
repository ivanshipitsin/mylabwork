#include "LineForm.h"

void sum (LineFormR * left, LineFormR * right) {
    if (left->len >= right->len) {
        for (int i = 0; i < right->len; i++) {
            ((double *)left->head)[i] += ((double *)right->head)[i];
        }
    } else {
        for (int i = 0; i < left->len; i++) {
            ((double *)left->head)[i] += ((double *)right->head)[i];
        }
        add(left, ((double *)right->head) + left->len,  right->len - left->len);
    }
}


void sumc (LineFormC * left, LineFormC * right) {
    if (left->len >= right->len) {
        for (int i = 0; i < right->len; i++) {
            ((double complex *)left->head)[i] += ((double complex *)right->head)[i];
        }
    } else {
        for (int i = 0; i < left->len; i++) {
            ((double complex *)left->head)[i] += ((double complex*)right->head)[i];
        }
        add(left, ((double complex*)right->head) + left->len,  right->len - left->len);
    }
}
void comp(LineFormR * l, double scalr) {
    for (int i = 0; i < l->len; i++){
        ((double *)l->head)[i] *= scalr;
    }
}
void compc(LineFormC * l, double complex scalr) {
    for (int i = 0; i < l->len; i++){
        ((double complex *)l->head)[i] *= scalr;
    }
}

double func(LineFormR * l, double * argv, int argc) {
    double res = ((double*)l->head)[0];
    if (argc > l->len - 1) {
        argc = l->len - 1;
    }
    for (int i = 0; i < argc ; i++) {
        res += ((double *)l->head)[i + 1] * argv[i];
    }
    return res;
}

double complex funcc(LineFormC * l, double complex * argv, int argc) {
    double complex res  =((double complex *)l->head)[0];
    if (argc > l->len - 1) {
        argc = l->len - 1;
    }
    for (int i = 0; i < argc ; i++) {
        res += ((double complex *)l->head)[i + 1] * argv[i];
    }
    return res;
}

LineFormR * newLineFormR() {
    return makevector(sizeof(double));
}

LineFormC * newLineFormC() {
    return makevector(sizeof(double complex));
}

LineFormC * RtoC(LineFormR * l) {
    LineFormC * res = newLineFormC();
    for (int i = 0; i < l->len; i++) {
        double complex a = ((double *)l->head)[i];
        add(res, &a , 1);
    }
    return res;
}

LineFormR * newLineFormRn(double * a, int n) {
    LineFormR * res = newLineFormR();
    add(res, a, n);
    return res;
}

LineFormC * newLineFormCn(double complex * a, int n) {
    LineFormC * res = newLineFormC();
    add(res, a, n);
    return res;
}