#include <iostream>
#include <fstream>
#include "tree.hpp"
#include "students.hpp"
#include <string.h>
#include <sstream>
#include <random>
#include <time.h>
#include <cctype>
#include <vector>

static std::string FindGrop;

/// for test
void f(int * a){
	*a = *a % 2;
}

bool g(int a){
	return a%2;
}
/// 

bool FindFromGroup(Student elem){
	return elem.GetGroup() == FindGrop;
}

void PrintStudent(Student * elem){
	std::cout << elem->GetFirstName() << " " << elem->GetMiddleName() << " " << elem->GetLastName() << " " << elem->GetGroup() << std::endl;
}

void help(){
	std::cout << "find <type> [arg] -for search in database " << std::endl;
	std::cout << "rlist [num] -for print response" << std::endl;
	std::cout << "help -for this massage" << std::endl;
	std::cout << "q - for exit" << std::endl;
}

int main(int argc, char ** argv){
	if(argc == 1){
		std::vector<Tree<Student, int> *> responsis;
		bool exist = false;
		char Buffer[1024];
		std::ifstream ins("students.txt");
		std::ifstream intch("teacher.txt");
		if(!ins.is_open()){
			std::cerr << "FILE students.txt NO OPEN" << std::endl;
		}
		if(!intch.is_open()){
			std::cerr << "FILE teacher.txt NO OPEN" << std::endl;
		}
		Tree<Student,int> students;
		std::string group, name1, name2, name3;
		int id;
		std::string tmp;
		while(!ins.eof()){
			ins >> group;
			ins >> tmp;
			while(isdigit(tmp[0])){
				ins >> name1 >> name2 >> name3;
				Student typicalstudent(name1, name2, name3, group);
				id = std::stoi(tmp);
				students.addNode(id, typicalstudent);
				ins >> tmp;
			}
		}
		while(!exist){
			std::cout << "Enter command" << std::endl;
			std::cin.getline(Buffer,1024);
			std::stringstream stream;
			stream << Buffer;
			std::string funct;
			stream >> funct;
			if(funct == "find"){
				std::string param;
				stream >> param;
				if(param == "group"){
					std::string arg;
					stream >> arg;
					if(arg.length() > 0){
						FindGrop = arg;
						Tree<Student,int> * respons = students.where(FindFromGroup);
						responsis.push_back(respons);
						std::cout << "Respons save" << std::endl;
					}else{
						std::cout << "Error command" << std::endl;
					}
				}else{
					std::cout << "Error command" << std::endl;
				}
			} else if(funct == "q"){
				exist = true;
			} else if(funct == "help"){
				help();
			}else if(funct == "rlist"){
				unsigned int param;
				stream >> param;
				if((param < responsis.size() + 1) && (param > 0)){
					responsis[param - 1]->map(PrintStudent);
				}else {
					std::cout << "Error command" << std::endl;
				}
			}else {
				std::cout << "Error command, command \"help\" for help)" << std::endl;
			}
		}
		ins.close();
		intch.close();
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
