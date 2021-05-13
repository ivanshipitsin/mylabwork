#include <iostream>
#include "sequence.hpp"
#include <string>
#include "matrix.hpp"
#include <complex>
#include "unit.hpp"

const std::string MSG[] = {"1.EXIT", "2.Enter matrix (in real)", "3. Enter matrix (in complex)", "4. SUM (NUM1, NUM2)", "5. Scalar (NUM, SCLAR)" , "6. NORM (NUM)" , "7. List Matrix" };
const int SMSG = 7;

int getmenu() {
    std::string error = "";
    int ch = 0;
    do {
        std::cout << error;
        error = "You're wrong. Try again!";
        for (int i = 0; i < SMSG; i++) {
            std::cout << MSG[i] << std::endl;
        }
        std::cout << "Make your choice: ";
        ch = getchar() - '0';
        while (getchar() != '\n') {}
    } while(ch < 1 || ch > SMSG);

    return ch;
}


template<class T>
void printMatrixis(const ArraySequence<Matrix<T>>&);

int main() {
    ArraySequence<Matrix<double>> matdd;
    ArraySequence<Matrix<std::complex<double> > > matcc;
    bool turn = true;
        while(turn) {
            int ch = getmenu();
            switch (ch) {
                case 1:
                    turn = 0;
                    break;
                case 2:{
                        double ** temp;
                        int n = 0;
                        std::cout << "Enter dimention:\n";
                        std::cin >> n;
                        /*if(!scanf("%d", &n)) {
                            fprintf(stderr, "Error enter dimention\n");
                            break;
                        }*/
                        std::cout << "Enter Matrix:\n";
                        temp = read<double>(std::cin, n);
                        Matrix<double> newmatr(temp, n);
                        matdd.Append(newmatr);
                        scanf("%*c");
                        clear<double>(temp, n);
                        break;
                    }
                case 3: {
                        std::complex<double> ** temp;
                        int n = 0;
                        std:: cout << "Enter dimention:\n";
                        std::cin >> n;
                        /*if(!scanf("%d", &n)) {
                            fprintf(stderr, "Error enter dimention\n");
                            break;
                        }*/
                        std::cout << "Enter Matrix:\n";
                        temp = read<std::complex<double>>(std::cin, n);
                        Matrix<std::complex<double>> newmat(temp, n);
                        matcc.Append(newmat);
                        scanf("%*c");
                        clear<std::complex<double>>(temp, n);
                        break;
                    }
                case 4:{
                    std::cout << "For complex(1) or real(2)?\n";
                    int real = 1;
                    std::cin >> real;
                    std::cout << "Man: SUM(NUM1,NUM2) =: NEWNUM = NUM1 + NUM2\n";
                    std::cout << "Enter NUM1:";
                    int num1 = 0, num2 = 0;
                    std::cin >> num1;
                    std::cout << "Enter NUM2:";
                    std::cin >> num2;
                    
                    if(real == 2) {
                        Matrix<double> temp = matdd.Get(num1 - 1) + matdd.Get(num2 - 1);
                        matdd.Append(temp);
                        std::cout << "New Number for your matrix :" << matdd.GetLenght();
                    } else if( real == 1){
                        Matrix<std::complex<double>> temp = matcc.Get(num1 - 1) + matcc.Get(num2 - 1);
                        matcc.Append(temp);
                        std::cout << "New Number for your matrix :" << matcc.GetLenght();
                    }

                    scanf("%*c");
                    break;
                }
                case 5:{
                    std::cout << "For complex(1) or real(2)?\n";
                    int real = 1;
                    std::cin >> real;
                    printf("Man: Scalar(NUM,SCLAR) =:  NEWNUM = NUM * SCLAR\n");
                    int NUM = 0;
                    printf("Enter NUM:");
                    std::cin >> NUM;
                    if(real == 2){
                        double scal;
                        std::cout << "Enter Scalar:";
                        std::cin >> scal;
                        Matrix<double> temp = matdd.Get(NUM - 1) * scal;
                        matdd.Append(temp);
                        std::cout << "New number for your matrix:" << matdd.GetLenght();
                    } else if(real == 1) {
                        std::complex<double> scal;
                        std::cout << "Enter Scalar:";
                        std::cin >> scal;
                        Matrix<std::complex<double>> temp = matcc.Get(NUM - 1) * scal;
                        matcc.Append(temp);
                        std::cout << "New number for your matrix:" << matcc.GetLenght();
                    }

                    scanf("%*c");
                    break;
                }
                case 6:{
                        std::cout << "For complex(1) or real(2)?\n";
                        int real = 1;
                        std::cin >> real;
                        std::cout << "Man: NORM(NUM) =: res = NUM(ARGV)\n";
                        std::cout << "Enter NUM:";
                        int num = 0;
                        std::cin >> num;
                        double res = 0;
                        if(real == 2){
                            try{
                                res = matdd.Get(num - 1).norm();
                            } catch(const char* s){
                                std::cerr << s << std::endl;
                                break;
                            }
                        } else if(real == 1){
                            try{
                                res = matcc.Get(num - 1).norm();
                            } catch(const char * s){
                                std::cerr << s << std::endl;
                                break;
                            }
                            
                        }
                        std::cout << "Result:" << res << std::endl;
                        scanf("%*c");
                        break;
                    }
                case 7:
                    std::cout << "Real Matrix :";
                    printMatrixis<double>(matdd);
                    std::cout << "Complex Matrix :";
                    printMatrixis<std::complex<double>>(matcc);
                    break;
            }
        }
    

    /*int ** masivblackhole = new int *[4];
    for(int i = 0; i < 4; i++){
        masivblackhole[i] = new int[4];
        for(int j = 0; j < 4; j++){
            masivblackhole[i][j] = i + j;
        }
    }
    Matrix<int>* matr = new Matrix<int>(masivblackhole, 4);
    Matrix<int>* res = matr->Scalar(5);
    for(int i = 0; i < res->GetDim(); i++){
        for(int j = 0; j < res->GetDim(); j++) {
            std::cout << res->Get(i,j) << ' ';
        }
        std::cout << std::endl;
    }
    
    delete matr;
    delete res;
    for(int i=0; i<4;i++){
        delete [] masivblackhole[i];
    }
    delete [] masivblackhole;
    return 0;*/
}





template<class T>
void printMatrixis(const ArraySequence<Matrix<T>> & data) {
    for(int i = 0; i < data.GetLenght(); i++){
        std::cout << std::endl;
        Matrix<T> item;
        try{
            item = data.Get(i); // maybe error
        }catch(char const * s) {
            std::cerr << s << " " << i  << "in printMatrix : item = data.Get(i)"<< data.GetLenght() <<std::endl;
        }
        std::cout << "Number:" << i << std::endl;
        for(int j = 0 ; j < item.GetDim(); j++) {
            for(int k = 0; k < item.GetDim(); k++){
                try{
                    std::cout << item.Get(j,k) << " ";
                }catch( char const* s){
                    std::cerr << s << std::endl;
                }
            }
            std::cout << std::endl;
        }
    }
}