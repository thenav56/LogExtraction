main: main.o 
		g++ -o logext main.o

main.o: include/fptree.h include/cluster.h main.cpp
		g++ -c main.cpp -std=c++11
clean:
	rm -rf *o logext
