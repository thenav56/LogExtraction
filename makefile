main: main.o 
		g++ -o output main.o

main.o: fptree.h cluster.h main.cpp
		g++ -c main.cpp -std=c++11
clean:
	rm -rf *o output
