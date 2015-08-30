main: main.o 
		g++ -o output main.o

main.o: HMM.h regex_key_value.h main.cpp
		g++ -c main.cpp -std=c++11
clean:
	rm -rf *o output
