#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <list>
#include <string>

using namespace std;

template<class T>
class HMM{
private:
	map<string, int> tags;
	map<string, double> probtt, probwt;
	
public:
	HMM() {}
	void Train(vector<vector<T>> & tlogs){
		for(auto i=tlogs.begin(); i != tlogs.end(); ++i){
			for(auto j= i->begin(); j != i->end(); ++j){
				map<string, int>::iterator it = tags.find(j->second);
				if( it != tags.end())
					it->second = it->second + 1;
				else{
					tags.insert(make_pair(j->second, 1));
				}
			}
		}
		//calculation of transition probability
		for(auto i=tlogs.begin(); i != tlogs.end(); ++i){
			for (int j = 0; j + 1 < i->size(); ++j) {
				string tt = (*i)[j].second + (*i)[j + 1].second;
				map<string, double>::iterator it = probtt.find(tt);
				if(it != probtt.end()){
					it->second += 1/tags[(*i)[j].second];
				}
				else{
					probtt.insert(make_pair(tt, 1/tags[(*i)[j].second]));
				}
				cout<<tt<<"\n";
			}
		}
		for(auto i=tags.begin(); i != tags.end(); ++i){
			cout<<i->first<"\t";
			cout<<i->second<<"\n";
		}
	}

};
