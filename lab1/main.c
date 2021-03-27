#include "vector.h"
#include "LineForm.h"
#include "test.h"
#include "utilit.h"
#include <stdio.h>

const char * MSG[] = {"1.EXIT", "2.Enter lineform (in real)", "3. Enter lineform (in complex)", "4. SUM (NUM1, NUM2)", "5. COMP (NUM, SCLAR)" , "6. FUNC (NUM, ARGV)" , "7. List lineform" };
const int SMSG = 7;

void printLineform(vector **, int);
int getmenu() {
    char * error = "";
    int ch = 0;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < SMSG; i++) {
            puts(MSG[i]);
        }
        puts("Make your choice: ");
        ch = getchar() - '0';
        while (getchar() != '\n') {}
    } while(ch < 1 || ch > SMSG);

    return ch;
}

int main(int argc, char** argv) {
    printf("Hello in my programmshit\n");
    int turn = 1;
    int count = 0;
    vector ** a = NULL;
    if (argc < 2) {
        while(turn) {
            int ch = getmenu();
            switch (ch) {
                case 1:
                    turn = 0;
                    break;
                case 2:{
                        double * temp;
                        int n = 0;
                        printf("Enter dimention:\n");
                        if(!scanf("%d", &n)) {
                            fprintf(stderr, "Error enter dimention\n");
                            break;
                        }
                        printf("Enter lineform:\n");
                        temp = read(stdin, n);
                        if(!temp) {
                            fprintf(stderr, "Error enter lineform");
                            break;
                        }
                        a = (vector **)realloc(a, (count + 1) * sizeof(vector *));
                        a[count] = newLineFormRn(temp, n);
                        count++;
                        scanf("%*c");
                        free(temp);
                        break;
                    }
                case 3: {
                        double complex* temp;
                        int n = 0;
                        printf("Enter dimention:\n");
                        scanf("%d", &n);
                        printf("Enter lineform: (in the pair)\n");
                        temp = readc(stdin, n);
                        a = (vector **)realloc(a, (count + 1) * sizeof(vector *));
                        a[count] = newLineFormCn(temp, n);
                        count++;
                        scanf("%*c");
                        free(temp);
                        break;
                    }
                case 4:{
                    printf("Man: SUM(NUM1,NUM2) =:  NUM1 = NUM1 + NUM2\n");
                    printf("Enter NUM1:");
                    int num1 = 0, num2 = 0;
                    scanf("%d" , &num1);
                    printf("Enter NUM2:");
                    scanf("%d", &num2);
                    if(num1 > count || num2 > count || num1 < 1 || num2 < 1) {
                        fprintf(stderr, "ERROR, vector don\'t found\n");
                        scanf("%*c");
                        break;
                    }
                    if (a[num1 - 1] ->size < sizeof(double complex) && a[num2 - 1] -> size < sizeof(double complex)){
                        sum(a[num1 - 1], a[num2 - 1]);
                    } else if (a[num1 - 1] ->size == a[num2-1] -> size ) {
                        sumc(a[num1 - 1], a[num2 - 1]);
                    } else {
                        if(a[num1 - 1] -> size == sizeof(double complex)){
                            //sumcr(a[num1 - 1], a[num2 - 1]);
                            LineFormC * res = RtoC(a[num2 - 1]);
                            sumc(a[num1 - 1], res);
                            deletevector(res);
                        } else {
                            LineFormC * res = RtoC(a[num1 - 1]);
                            sumc(res, a[num2 - 1]);
                            deletevector(a[num1 - 1]);
                            a[num1 - 1] = res;
                        }
                    }
                    scanf("%*c");
                    break;
                }
                case 5:{
                    printf("Man: COMP(NUM,SCLAR) =:  NUM = NUM * SCLAR\n");
                    int NUM = 0;
                    printf("Enter NUM:");
                    int res = scanf("%d" , &NUM);
                    if (NUM > count || NUM < 1) {
                        fprintf(stderr, "ERROR, vector don\'t found\n");
                        scanf("%*c");
                        break;
                    }
                    if (res  == 0) {
                        fprintf(stderr, "ERROR , incorrent data\n");
                        scanf("%*c");
                        break;
                    }
                    if (a[NUM - 1] -> size < sizeof(double complex)) {
                        double sclar = 0;
                        printf("Enter SCLAR:");
                        scanf("%lf", &sclar);
                        comp(a[NUM - 1], sclar);
                    } else {
                        printf("Enter SCLAR (in complex)");
                        double re, im;
                        scanf("%lf %lf", &re, &im);
                        double complex sclar;
                        __real__ sclar = re;
                        __imag__ sclar = im;
                        compc(a[NUM - 1], sclar);
                    }
                    scanf("%*c");
                    break;
                }
                case 6:{
                        printf("Man: FUNC(NUM, ARGV) =: res = NUM(ARGV)\n");
                        printf("Enter NUM:");
                        int num = 0;
                        scanf("%d", &num);
                        if (num > count || num < 1) {
                            fprintf(stderr, "ERROR, vector don\'t found\n");
                            scanf("%*c");
                            break;
                        }
                        int mun = 0;
                        printf("Enter amount arguments :");
                        scanf("%d", &mun);
                        if (a[num - 1] -> size < sizeof(double complex)) {
                            double res = 0;
                            printf("Enter arguments:\n");
                            double * p = read(stdin, mun);
                            res = func(a[num - 1], p, mun);
                            printf("%lf", res);
                            free(p);
                        } else {
                            double complex res;
                            printf("Enter arguments (in pair):\n");
                            double complex * p = readc(stdin, mun);
                            res = funcc(a[num - 1], p, mun);
                            printf("%lf + %lf*I", __real__ res, __imag__ res);
                            free(p);
                        }
                        scanf("%*c");
                        break;
                    }
                case 7:
                    printLineform(a, count);
                    break;
                default:
                    printf("AAAAAA. zzzzzzzz\n");
                    break;
            }
        }
    } else {
        if (!strcmp(argv[1], "test")) {
            test();
        }
    }

    for (int i = 0; i < count; i++) {
        deletevector(a[i]);
    }
    free(a);
    return 0;
}


void printLineform(vector ** a, int n) {
    for (int i = 0; i < n; i++) {
        printf("L%d:", i + 1);
        int m = a[i] -> len;
        if (a[i] -> size < sizeof(double complex)) {
            for (int j = 0; j < m; j++) {
                printf("%6lf ", ((double *)a[i]->head)[j]); 
            }
        } else {
            for (int j = 0; j < m; j++) {
                printf("%6lf + %6lf * I ", creal(((double complex *)a[i]->head)[j]) , cimag(((double complex *)a[i]->head)[j])); 
            }
        }
        printf("\n");
    }    
}
