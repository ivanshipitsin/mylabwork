#include "test.h"

int testmakevector() { // test 1
    vector * newvector = makevector(10);
    if (!newvector) {
        fprintf(stdout, "testmakevector(): MAKEVECTOR RETURN NULL\n");
        return -1;
    }
    if (newvector->size != 10) {
        fprintf(stdout, "testmakevector(): MAKEVECTOR INVALID SIZE\n");
        return 1;
    }
    deletevector(newvector);
    newvector = makevector(0);
    if (newvector) {
        fprintf(stdout, "testmakevector(): MAKEVECTOR INVALID SIZE 0\n");
        return 2;
    }
    return 0;
}

int testaddvector() { // test 2
    vector * new = makevector(4);
    int a[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int res = 0;
    res = add(new, a, 20);
    if (res == -1) {
        fprintf(stdout ,"testaddvector(): ERROR REALLOC DATA\n");
        deletevector(new);
        return -1;
    } else if( res == -2)  {
        fprintf(stdout, "testaddvector(): ERROR MEMCPY DATA\n");
        deletevector(new);
        return -2;
    }
    return 0;
}

int testsum() {
    FILE * tsfile = fopen("test/sum.test","r");
    if (!tsfile) {
        fprintf(stderr, "testsum(): TEST FILE NOT FOUND\n");
        return -1;
    }
    int n = 0; // amount test
    fscanf(tsfile, "%d", &n);
    for (int i = 1; i <= n; i++) {
        int n1, n2, n3;
        fscanf(tsfile, "%d", n1);
        double *a1 = (double *)calloc(n1, sizeof(double));
        for (int j = 0; j < n1; j++){
            fscanf(tsfile, "%lf", a1 + j);
        }

        fscanf(tsfile, "%d", n2);
        double *a2 = (double *)calloc(n2, sizeof(double));
        for (int j = 0; j < n2; j++){
            fscanf(tsfile, "%lf", a2 + j);
        }
        fscanf(tsfile, "%d", n3);
        double *a3 = (double *)calloc(n3, sizeof(double));
        for (int j = 0; j < n3; j++){
            fscanf(tsfile, "%lf", a3 + j);
        }

        LineFormR * v1 = newLineFormRn(a1, n1);
        LineFormR * v2 = newLineFormRn(a2, n2);
        LineFormR * v3 = newLineFormRn(a3, n3);
        sum(v1, v2);
        if (n1 != n3 || memcmp(v1->head, v3->head, n1)) {
            fprintf(stdout ,"testsum(): ERORR SUM in test: %d" , i);
            deletevector(v1);
            deletevector(v2);
            deletevector(v3);
            free(a1);
            free(a2);
            free(a3);
            return -i;
        }
        deletevector(v1);
        deletevector(v2);
        deletevector(v3);
        free(a1);
        free(a2);
        free(a3);
    }
    return 0;
}

int testsum() {
    FILE * tsfile = fopen("test/sumc.test","r");
    if (!tsfile) {
        fprintf(stderr, "testsumc(): TEST FILE NOT FOUND\n");
        return -1;
    }
    int n = 0; // amount test
    fscanf(tsfile, "%d", &n);
    for (int i = 1; i <= n; i++) {
        int n1, n2, n3;
        fscanf(tsfile, "%d", n1);
        double complex *a1 = (double complex *)calloc(n1, sizeof(double complex));
        double real = 0, im = 0;
        for (int j = 0; j < n1; j++){
            fscanf(tsfile, "%lf %lf", &real, &im);
            __real__ (a1[j]) = real;
            __imag__ (a1[j]) = im;
        }

        fscanf(tsfile, "%d", n2);
        double complex *a2 = (double complex*)calloc(n2, sizeof(double complex));
        for (int j = 0; j < n2; j++){
            fscanf(tsfile, "%lf %lf", &real, &im);
            __real__ (a2[j]) = real;
            __imag__ (a2[j]) = im;
        }
        fscanf(tsfile, "%d", n3);
        double complex *a3 = (double complex *)calloc(n3, sizeof(double complex));
        for (int j = 0; j < n3; j++){
            fscanf(tsfile, "%lf %lf", &real, &im);
            __real__ (a3[j]) = real;
            __imag__ (a3[j]) = im;
        }

        LineFormC * v1 = newLineFormCn(a1, n1);
        LineFormC * v2 = newLineFormCn(a2, n2);
        LineFormC * v3 = newLineFormCn(a3, n3);
        sumc(v1, v2);
        if (n1 != n3 || memcmp(v1->head, v3->head, n1)) {
            fprintf(stdout ,"testsumc(): ERORR SUM in test: %d" , i);
            deletevector(v1);
            deletevector(v2);
            deletevector(v3);
            free(a1);
            free(a2);
            free(a3);
            return -i;
        }
        deletevector(v1);
        deletevector(v2);
        deletevector(v3);
        free(a1);
        free(a2);
        free(a3);
    }
    return 0;
}

int testcomp() {
    FILE * tcfile = fopen("test/comp.test","r");
    if (!tcfile) {
        fprintf(stderr, "testcomp(): TEST FILE NOT FOUND\n");
        return -1;
    }
    int n = 0; // amount test
    fscanf(tcfile, "%d", &n);
    for (int i = 1; i <= n; i++) {
        int n1;
        double scalr;
        fscanf(tcfile, "%d", n1);
        double *a1 = (double *)calloc(n1, sizeof(double));
        for (int j = 0; j < n1; j++){
            fscanf(tcfile, "%lf", a1 + j);
        }
        fscnaf(tcfile, "%lf", scalr);
        double *a2 = (double *)calloc(n1, sizeof(double));
        for (int j = 0; j < n1; j++){
            fscanf(tcfile, "%lf", a2 + j);
        }

        LineFormR * v1 = newLineFormRn(a1, n1);
        LineFormR * v2 = newLineFormRn(a2, n1);
        comp(v1, scalr);
        if (memcmp(v1->head, v2->head, n1)) {
            fprintf(stdout ,"testcomp(): ERORR COMP in test: %d" , i);
            deletevector(v1);
            deletevector(v2);
            free(a1);
            free(a2);
            return -i;
        }
        deletevector(v1);
        deletevector(v2);
        free(a1);
        free(a2);
    }
    return 0;
}


int testcompc() {
    FILE * tcfile = fopen("test/compc.test","r");
    if (!tcfile) {
        fprintf(stderr, "testcompc(): TEST FILE NOT FOUND\n");
        return -1;
    }
    int n = 0; // amount test
    fscanf(tcfile, "%d", &n);
    for (int i = 1; i <= n; i++) {
        int n1;
        double complex scalr;
        double real, im;
        fscanf(tcfile, "%d", n1);
        double complex *a1 = (double complex*)calloc(n1, sizeof(double complex));
        for (int j = 0; j < n1; j++){
            fscanf(tcfile, "%lf %lf", &real, &im);
            __real__ (a1[j]) = real;
            __imag__ (a1[j]) = im;
        }
        fscnaf(tcfile, "%lf %lf", &real, &im);
        __real__ scalr = real;
        __imag__ scalr = im;
        double complex *a2 = (double complex *)calloc(n1, sizeof(double complex));
        for (int j = 0; j < n1; j++){
             fscanf(tcfile, "%lf %lf", &real, &im);
            __real__ (a2[j]) = real;
            __imag__ (a2[j]) = im;
        }

        LineFormC * v1 = newLineFormCn(a1, n1);
        LineFormC * v2 = newLineFormCn(a2, n1);
        compc(v1, scalr);
        if (memcmp(v1->head, v2->head, n1)) {
            fprintf(stdout ,"testcomp(): ERORR COMP in test: %d" , i);
            deletevector(v1);
            deletevector(v2);
            free(a1);
            free(a2);
            return -i;
        }
        deletevector(v1);
        deletevector(v2);
        free(a1);
        free(a2);
    }
    return 0;
}

int test() {
    int res[12] = {0};

    res[0] = testmakevector(); 
    res[1] = testaddvector();

    res[2] = testsum(); 
    res[3] = testsumc();
    res[4] = testcomp();
    res[5] = testcompc();
    res[6] = testfunc();
    res[7] = testfuncc();

    res[8] = testnewlineformr(); 
    res[9] = testnewlineformc();
    res[10] = testnewlineformrn();
    res[11] = testnewlineformcn();

}

