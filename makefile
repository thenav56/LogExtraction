apriori: apriori.o 
	g++ -o apriori apriori.o

apriori.o: apriori.cpp
	g++ -c apriori.cpp -std=c++11
