#ifndef ANALYZE_H
#define ANALYZE_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;
template <class T>
class Analyze{
private:

public:
	double Efficiency(vector<vector<T>> & output, vector<vector<T>> & manual){
		int total=0, match=0;
		auto  j = manual.begin();
		for(auto i = output.begin(); i != output.end(); ++i, ++j){
			auto l = j->begin();
			for(auto k = i->begin(); k != i->end(); ++k, ++l){
					if(k->second == l->second)
						match++;
					total++;
			}
		}
		return (match*100.0/total);
	}


};





#endif