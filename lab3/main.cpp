#include <iostream>
#include "tree.hpp"
#include <string.h>
#include <random>
#include <time.h>
int main(int argc, char ** argv){
	if(argc == 1){
		Tree<int,int> a;
		srand(time(nullptr));
		for(int i = 0; i < 23; i++){
			a.addNode(i, rand()%10000000);
		}
		std::cout << (int)a.HE()<< "\n";
		a.printTree();
		std::cout << "\t\t---\t\t" << std::endl;
		try{
			for(int i = 2; i <20 ; i++){
				a.deleteNode(i);
				if(i == 9 || i == 8){
					a.printTree();
					std::cout << "\t\t---\t\t" << std::endl;
				}
			}
		}catch(int s){
			std::cerr << "Error Delete Node " << s << std::endl;
			a.printTree();
		}

		std::cout << (int)a.HE()<< "\n";
	} else if(argc > 1 && !(strcmp(argv[1],"crash"))){
		Tree<int,int> a;
		int key = 0,value = 0;
		srand(time(nullptr));
		for(int i = 0; i < 100000000; i++){
			key = i;
			value = rand() % 1000000000;
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
