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
        fprintf(stdout, "testaddvecotr(): ERROR MEMCPY DATA\n");
        deletevector(new);
        return -2;
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