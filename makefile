fpgrowth: fpgrowth.o 
		g++ -o fpgrowth fpgrowth.o

fpgrowth.o: fptree.h fpgrowth.cpp
		g++ -c fpgrowth.cpp -std=c++11
