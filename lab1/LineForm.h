#ifndef _LINEFORM_
#define _LINEFORM_
#include "vector.h"
#include <complex.h>

typedef vector LineFormR; // have size = sizeof(double)
typedef vector LineFormC; // have size = sizeof(double complex)

void comp(LineFormR *, double);
void compc(LineFormC *, double complex);
void sum (LineFormR *, LineFormR *);
void sumc (LineFormC *, LineFormC *);
double func(LineFormR *, double *, int);
double complex funcc(LineFormC *, double complex *, int);
LineFormR * newLineFormR();
LineFormR * newLineFormRn(double *, int);
LineFormC * newLineFormC();
LineFormC * newLineFormCn(double complex *, int);
LineFormC * RtoC(LineFormR *);
#endif