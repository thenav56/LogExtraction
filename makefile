apriori: apriori.o 
	g++ -o apriori apriori.o

apriori.o:
	g++ -c apriori.cpp -std=c++11
