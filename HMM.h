#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <list>
#include <string>

using namespace std;

typedef pair<string, string> V;

template<class T>
class HMM{
private:
	vector<vector<V>> tlogs;
	map<string, int> tags;
	map<string, double> probtt, probwt;
	vector<pair<string, double>> best_score, key;
	map<map<int, string>, map<int, string>> best_edge;
	
public:
	HMM() {}
	void Train(vector<vector<T>> & lfile, vector<vector<T>> & tfile){
		//Associate tags with logs
		{
			auto i=lfile.begin(); auto j=tfile.begin(); 
			for(;i!=lfile.end(); ++i, ++j){
				vector<V> temp;
				auto k=i->begin(); auto l=j->begin();
				for(;k!=i->end(); ++k, ++l){
					temp.emplace_back(k->second,l->second);
				}
				tlogs.push_back(temp);
			} 
		}
		
		//identification of tags and thier count
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
					it->second += 1.0/tags[j->second];
				}
				else{
					probtt.insert(make_pair(tt, 1.0/tags[j->second]));
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
							it->second += 1.0/tags[j->second];
					}
					else{
						if(j->second.compare(k->first) == 0)
							probwt.insert(make_pair(wt,1.0/tags[j->second]));
						else
							probwt.insert(make_pair(wt,0));
					}
				}
			}
		}
		/*
		for(auto i=probtt.begin(); i != probtt.end(); ++i){
			cout<<i->first<"\t";
			cout<<i->second<<"\n";
		}
		for(auto i=probwt.begin(); i != probwt.end(); ++i){
			cout<<i->first<"\t";
			cout<<i->second<<"\n";
		}
		*/
	}

	void ForwardViterbi(vector<T> & logs){
		
		//From REgex
		for(auto i=logs.begin(); i!=logs.end(); ++i){
			if(i->first == 0){
				key.push_back(make_pair("ip", 1));
			}
			else if(i->first == 3){
				key.push_back(make_pair("time", 1));
			}
			else 
				key.push_back(make_pair("", -1));
		}
		//map<pair<int,string>, double>::iterator it = best_score.begin();
		for(auto i=logs.begin(); i!=logs.end(); ++i){
			best_score.push_back(make_pair("",0.0));
			if(key[i->first].second != -1){
				best_score[i->first].first = key[i->first].first;
				best_score[i->first].second = best_score[i->first -1].second;
				continue;

			}
			if(i->first == 0){
				for(auto j = tags.begin(); j != tags.end(); ++j){
					for(auto k = tags.begin(); k != tags.end(); ++k){
						double score = 2*probwt[i->second+j->first] + probtt[j->first + k->first] + 2*probwt[(i+1)->second + k->first];
						//cout<<probwt[i->second+j->first]<<":"<<probtt[j->first + k->first]<<":"<<probwt[(i+1)->second + k->first]<<"\n";
						if(best_score[i->first].second < score){
							best_score[i->first].first = j->first;
							best_score[i->first].second = score;
						}
					}
				}
				continue;
			}
			for(auto j = tags.begin(); j != tags.end(); ++j){
				double score = best_score[i->first -1].second + probtt[best_score[i->first -1].first + j->first]
				+ probwt[i->second+j->first];
				if(best_score[i->first].second < score){
					best_score[i->first].first = j->first;
					best_score[i->first].second = score;
				}

			}
		}
		auto k=logs.begin();
		for(auto i=best_score.begin(); i != best_score.end(); ++i, ++k){
			cout<<i->first<<": ";
			cout<<k->second<<"\t";
		}
		cout<<"\n";
		cout<<"\n";
		best_score.clear();
		key.clear();
	}

	void TagLogs(vector<vector<T>> & logs){
		for(auto i=logs.begin(); i!=logs.end(); ++i)
			ForwardViterbi(*i);
		
	}

};

