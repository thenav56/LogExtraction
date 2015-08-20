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
			for(auto j=i->begin(); j!=i->end(); ++j){
				if(j == i->end()-1) break;
				string tt = j->second + (j+1)->second;
				
				map<string, double>::iterator it = probtt.find(tt);
				if(it != probtt.end()){
					it->second += 1/tags[j->second];
				}
				else{
					probtt.insert(make_pair(tt, 1/tags[j->second]));
				}
				
				
			}
		}

		//calculation of emission probability
		for(auto i=tlogs.begin(); i != tlogs.end(); ++i){
			for(auto j=i->begin(); j != i->end(); ++j){
				for(auto k = tags.begin(); k != tags.end(); ++k){
					string wt = j->first + k->first;

					map<string, double>::iterator it = probwt.find(wt);
					if(it != probwt.end()){
						if(j->second.compare(k->first) == 0)
							it->second += 1;
					}
					else{
						if(j->second.compare(k->first) == 0)
							probwt.insert(make_pair(wt,1));
						else
							probwt.insert(make_pair(wt,0));
					}
				}
			}
		}


		for(auto i=probwt.begin(); i != probwt.end(); ++i){
			cout<<i->first<"\t";
			cout<<i->second<<"\n";
		}

	}

};