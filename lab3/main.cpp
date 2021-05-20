#include <iostream>
#include "tree.hpp"
#include <string.h>
#include <random>
#include <time.h>
int main(int argc, char ** argv){
	if(argc == 1){
		Tree<int,int> a;
		a.addNode(1,1);
		a.addNode(3,1);
		a.addNode(2,1);
		a.addNode(2,2);
		try{
			a.deleteNode(2);
		}catch(const char* s){
			std::cerr << s << std::endl;
		}
		std::cout << "endl" << std::endl;
	} else if(argc > 1 && !(strcmp(argv[1],"crash"))){
		Tree<int,int> a;
		int key = 0,value = 0;
		srand(time(nullptr));
		for(int i = 0; i < 100000000; i++){
			key = rand() % 1000000000;
			value = rand() % 1000000000;
			a.addNode(key,value);
		}
		std::cout << a.HE() << std::endl;
	}
	return 0;
}
