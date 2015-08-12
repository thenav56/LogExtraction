#include <iostream>
#include <vector>
#include <map>

template <class T>
class Cluster{
private:
	std::vector<std::vector<T>> logs;
	std::vector<std::pair<int, int>> best_lines;

	std::vector<int> log_count;
	std::map<std::vector<T>, std::vector<int>> logsWithPattern;

public:
	Cluster() {}
	/*
		void setnewbest(std::vector<std::vector<T>> & mp, std::vector<std::vector<T>> & logs) {
			{
				int num;
				auto i = mp.begin();
				for (i, num = 0; i != mp.end(); ++i, ++num) { //pattern
					for (int j = 0; j < (int)logs.size(); ++j) {
						bool ok = 1;
						for (auto k = i->first.begin(); k != i->first.end() && ok; ++k) {
							ok = logs[j].find(*k) != logs[j].end();
						}
						if (ok && i->first.size() > best_lines[j].size()) {
							best_lines[j] = num;
						}
					}
				}
			}
		}
		void cluster(const std::vector<std::vector<T>> & logs, std::vector<std::vector<T>> & pattern_bin)
		{
			std::vector<std::vector<T>> clustered_logs;
			{
				int num;
				auto i = pattern_bin.begin();
				for (i, num = 0; i != pattern_bin.end(); ++i, ++num) { //pattern
					for (int j = 0; j < (int)logs.size(); ++j) {
							if(num == best_lines[j])
							{
								log_count[num] += 1;
								clustered_logs.push_back(logs[j]);
							}
					}
				}
				for(auto &i : clustered_logs){
					std::cout<<i.second<<"\n"

				}
			}
		} */
		void AssociatePatterns(std::vector<std::vector<T>> & logs, std::vector<std::vector<T>> & pattern_bin){
			for(int j=0; j<(int)logs.size(); ++j){
				best_lines.emplace_back(0,0);
				for(auto i = pattern_bin.begin(); i != pattern_bin.end(); ++i){
					bool ok =1; 
					
					for(auto k = i->begin(); k != i->end() && ok; ++k){
						ok = std::find(logs[j].begin(), logs[j].end(), *k) != logs[j].end();
					}
					
					if(ok && i->size() > best_lines[j].second){
						best_lines[j].first = i - pattern_bin.begin(); //saves the line number of best pattern
						best_lines[j].second = i->size(); //saves the size of best pattern
					}
				}
			} 
			
			for(int i = 0; i < (int)logs.size(); ++i){
				logsWithPattern[pattern_bin[best_lines[i].first]].push_back(i);
			}
			
		}
		void AssociateLogs(std::vector<std::vector<T>> & logs, std::vector<std::vector<T>> & pattern_bin)
		{
			for(auto i = pattern_bin.begin(); i != pattern_bin.end(); ++i){
				for(int j=0; j<(int)logs.size(); j++){
					bool ok = 1;
					for(auto k = i->begin(); k != i->end() && ok; ++k)
						ok = std::find(logs[j].begin(), logs[j].end(), *k) != logs[j].end();
					
					if(ok)
						logsWithPattern[*i].push_back(j);

				}
			}
		}
		void DisplayCluster(std::vector<std::vector<T>> logs){
			for(auto i = logsWithPattern.begin(); i != logsWithPattern.end(); ++i){
				std::cout<<"Cluster Pattern:";
				for(auto j = i->first.begin(); j != i->first.end(); ++j){
					std::cout<<j->second<<" ";
				}
				std::cout<<"\n";
				for(auto j = i->second.begin(); j != i->second.end(); ++j){
					for(auto k : logs[*j]){
						std::cout<<k.second<<" ";
					}
					std::cout<<"\n";
				}
			}
				
		}

};
