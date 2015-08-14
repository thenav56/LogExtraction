#include <iostream>
#include <vector>
#include <map>

template <class T>
class Cluster{
private:
	std::vector<std::vector<T>> logs;
	std::vector<std::pair<int, int>> best_lines;

	std::vector<int> log_count;
	std::map<int, std::vector<int>> logsWithPattern;

public:
	Cluster() {}

	void AssociatePatterns(std::vector<std::vector<T>> & logs, std::vector<std::vector<T>> & pattern_bin){
		for(int j=0; j<(int)logs.size(); ++j){
			best_lines.emplace_back(NULL, NULL);
			std::vector<T> new_pattern, temp_pattern;
			for(auto i = pattern_bin.begin(); i != pattern_bin.end(); ++i){
				bool ok =0; 
				int count = 0;
				
				for(auto k = i->begin(); k != i->end(); ++k){
					if(std::find(logs[j].begin(), logs[j].end(), *k) != logs[j].end()){
						count++;
						temp_pattern.push_back(*k);
					}
				}
				
				if(count > best_lines[j].second){
					best_lines[j].first = i - pattern_bin.begin(); //saves the line number of best pattern
					best_lines[j].second = count; //saves the size of best pattern
					new_pattern.clear();
					new_pattern = temp_pattern;
				}
				temp_pattern.clear();
			}
			if(best_lines[j].second < pattern_bin[best_lines[j].first].size() && best_lines[j].second != 0){
				pattern_bin.push_back(new_pattern);
				best_lines[j].first = pattern_bin.end() - pattern_bin.begin() -1;
				
			}

		} 
		
		for(int i = 0; i < (int)logs.size(); ++i){
			if(best_lines[i].second != 0)
			logsWithPattern[best_lines[i].first].push_back(i);
		}
	}

	void DisplayCluster(std::vector<std::vector<T>> logs, std::vector<std::vector<T>> & pattern_bin){
		for(auto i : logsWithPattern){
			std::vector<bool> column(1000,0);
			std::cout<<"\nCluster Pattern: ";
			for(auto j = pattern_bin[i.first].begin(); j != pattern_bin[i.first].end(); ++j){
				column[j->first] = 1;
				//std::cout<<j->second<<" ";
			}
			for (auto j = logs[*i.second.begin()].begin(); j != logs[*i.second.begin()].end(); ++j) {
				if (column[j->first]) std::cout << "[" << j->second << "]" ; else std::cout << "#";
				std::cout << " ";
			}
			std::cout<<"\n";
			for(auto j = i.second.begin(); j != i.second.end(); ++j){
				for(auto k : logs[*j]){
					std::cout<<k.second<<" ";
				}
				std::cout<<"\n";
			}

		} 
	}

};
