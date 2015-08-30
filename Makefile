main: main.o 
		g++ -o output main.o -lboost_regex

main.o: HMM.h regex_key_value.h main.cpp
		g++ -Wall -std=c++11 -I/usr/include/boost -c main.cpp  
clean:
	rm -rf *o output
