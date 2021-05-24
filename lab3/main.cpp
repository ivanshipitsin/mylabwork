#include <iostream>
#include "tree.hpp"
#include <string.h>
#include <random>
#include <time.h>
void f(int * a){
	*a = *a % 2;
}

bool g(int a){
	return a%2;
}

int main(int argc, char ** argv){
	if(argc == 1){
		Tree<int,int> a;
		srand(time(nullptr));
		for(int i = 0; i < 10; i++){
			a.addNode(i, rand()%1000);
		}
		std::cout << (int)a.HE()<< "\n";
		a.printTree();
		std::cout << "\t\t---\t\t" << std::endl;
		Tree<int,int> * meh = a.where(g);
		meh->printTree();
		std::cout << (int)meh->HE()<< "\n";
		delete meh;
	} else if(argc > 1 && !(strcmp(argv[1],"crash"))){
		Tree<int,int> a;
		int key = 0,value = 0;
		srand(time(nullptr));
		for(int i = 0; i < 100000000; i++){
			key = i;
			value = rand() % 10;
			a.addNode(key,value);
		}
		std::cout << a.HE() << std::endl;
		try{
			for(int i = 10; i < 50000000; i++){
				a.deleteNode(i);
			}
		}catch(int s){
			std::cerr << "Not Found node" << s << std::endl;
		}
		std::cout << a.HE() << std::endl;
	}
	return 0;
}
