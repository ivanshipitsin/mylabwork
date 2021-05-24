#include <iostream>
#include <fstream>
#include "tree.hpp"
#include <sstream>
#include <random>
#include <time.h>

/// for test
void f(int * a){
	*a = *a % 2;
}

bool g(int a){
	return a%2;
}
/// 

void testadd(){
    std::ofstream out("tableadd.txt");
    for(int N = 10; N < 1000000; N+=1000){
        Tree<int,int> a;
        int * b = new int[N];
        for(int i = 0; i < N; i ++){
            b[i] = rand()%(N+120);
        }
        clock_t start = clock();
        for(int i = 0; i < N; i++){
            a.addNode(b[i] , 6);
        }
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        out << N << " " << seconds << std::endl;
    }
    out.close();
}

void testdelete(){
    std::ofstream out("tabledelete.txt");
    for(int N = 10; N < 1000000; N+=1000){
        Tree<int,int> a;
        for(int i = 0; i < N + 1000; i ++){
            a.addNode(i, 7);
        }
        clock_t start = clock();
        for(int i = 0; i < N; i++){
            a.deleteNode(N - i);
        }
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        out << N << " " << seconds << std::endl;
    }
    out.close();
}

void testfound(){
    std::ofstream out("tablefound.txt");
    for(int N = 10; N < 1000000; N+=1000){
        Tree<int,int> a;
        for(int i = 0; i < N + 1000; i ++){
            a.addNode(i, 7);
        }
        clock_t start = clock();
        for(int i = 15; i < N + 15; i++){
            Node<int,int> * ptr = a.foundNode(i);
            if(!ptr){
                std::cerr << "NODE NOT FOUNd " << i << std::endl;
            }
        }
        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;
        out << N << " " << seconds << std::endl;
    }
    out.close();
}

int main(int argc, char ** argv){
    srand(time(nullptr));
	testadd();
    testdelete();
    testfound();
	return 0;
}
