all:
	g++ -c main.cpp 
	g++ -o main main.o 

clear:
	rm *.o

debug:
	g++ -g -o main main.cpp
	g++ -g -o bench bench.cpp

bench:
	g++ -o bench bench.cpp