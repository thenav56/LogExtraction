main: main.o regex_key_value.o 
		g++-4.9 -o logext main.o regex_key_value.o

main.o: include/fptree.h include/cluster.h main.cpp
		g++-4.9 -c main.cpp -std=c++11

regex_key_value.o: include/regex_key_value.h src/regex_key_value.cpp
		g++-4.9 -c src/regex_key_value.cpp -std=c++11

clean:
	rm -rf *o logext
