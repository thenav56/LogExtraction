//APRIORI ALGORITHM NAIVE IMPLEMENTATION
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

const int THRESHOLD = 2;

typedef pair<int, string> PIS;

vector<set<PIS>> logs;
set<PIS> all_tokens;
vector<set<PIS>> best_lines;
//vector<int> best_cnt;
set<PIS> tokenize(string s) {
	istringstream is(s);
	set<PIS> res;
	string t;
	for (int i = 0; is >> t; ++i) {
		res.insert(make_pair(i, t));
		all_tokens.insert(make_pair(i, t));
	}
	return res;
}

void read(const char * file_name) {
	ifstream file(file_name);
	string s;
	while (getline(file, s)) {
		logs.push_back(tokenize(s));
	}
}
//complexity = O(ms.size()) , which is reasonable
map<set<PIS>, int> refine(const map<set<PIS>, int> & ms) {
	map<set<PIS>, int> res;
	for (auto i = ms.begin(); i != ms.end(); ++i) {
		if (i->second >= THRESHOLD) {
			res[i->first] = i->second;
		}
	}
	return res;
}
set<set<PIS>> candidate_list(const map<set<PIS>, int> & ms, bool emp) {
	set<set<PIS>> res;
	set<PIS> newtoks;
	for (auto i = ms.begin(); i != ms.end(); ++i) {
		for (auto j = i->first.begin(); j != i->first.end(); ++j) {
			newtoks.insert(*j);
		}
	}
	for (auto i = ms.begin(); i != ms.end(); ++i) {
		for (auto j = newtoks.begin(); j != newtoks.end(); ++j) {
			if (i->first.find(*j) == i->first.end()) {
				set<PIS> ns;
				if (!emp) ns = i->first;
				ns.insert(*j);
				res.insert(ns);
			}
		}
	}
	return res;
}
map<set<PIS>, int> countSets(const set<set<PIS>> & s) {
	map<set<PIS>, int> res;
	//count the total number of logs containing the set *i
	for (auto i = s.begin(); i != s.end(); ++i) {
		for (int j = 0; j < (int)logs.size(); ++j) {
			//check if log[j] contains the set *i
			bool ok = 1;
			for (auto k = i->begin(); k != i->end() && ok; ++k) {
				ok = logs[j].find(*k) != logs[j].end();
			}
			res[*i] += ok;
		}
	}
	return res;
}
void setnewbest(map<set<PIS>, int> & mp) {
	for (auto i = mp.begin(); i != mp.end(); ++i) {
		for (int j = 0; j < (int)logs.size(); ++j) {
			bool ok = 1;
			for (auto k = i->first.begin(); k != i->first.end() && ok; ++k) {
				ok = logs[j].find(*k) != logs[j].end();
			}
			if (ok && i->first.size() > best_lines[j].size()) {
				best_lines[j] = i->first;
			}
		}
	}
}
int main(int c, char ** args) {
	if (c == 1) {
		cout << "TEST PROGRAM\n";
		cout << "IMPLEMENTS THE APRIORI ALGORITHM TO FIND FREQUENT PATTERNS IN A DATA SET\n";
		cout << "Suitable only for small files\n";
		cout << "Program identifies common patterns in a log file\n";
		cout << "Usage: program_name log_file_name\n";
		return 0;
	}
	read(args[1]);
	map<set<PIS>, int> maxsets;
	for (int i = 0; i < (int)logs.size(); ++i) {
		for (auto j = logs[i].begin(); j != logs[i].end(); ++j) {
			set<PIS> ns;
			ns.insert(*j);
			maxsets[ns]++;
		}
	}
	maxsets = refine(maxsets);
	best_lines = vector<set<PIS>>(logs.size(), set<PIS>());
	//best_cnt = vector<int>(logs.size(), 0);
	for (int iter = 0; !maxsets.empty(); ++iter) {
		setnewbest(maxsets);
		set<set<PIS>> clist = candidate_list(maxsets, iter == 0);
		maxsets = countSets(clist);
		maxsets = refine(maxsets);
	}
	map<set<PIS>, set<int>> clusters;
	for (int i = 0; i < (int)logs.size(); ++i) {
		clusters[best_lines[i]].insert(i);
	}
	for (auto i : clusters) {
		vector<bool> consts(1000, 0); //maximum token length of each cluster
		for (auto itr = i.first.begin(); itr != i.first.end(); ++itr) {
			consts[itr->first] = 1;
		}
		cout << "Cluster Pattern: ";
		for (auto j = logs[*i.second.begin()].begin(); j != logs[*i.second.begin()].end(); ++j) {
			if (consts[j->first]) cout << "[" << j->second << "]" ; else cout << "#";
			cout << " ";
		}
		cout << "\n";
		for (auto j : i.second) {
			cout << "Line " << j + 1 << ": ";
			for (auto k : logs[j]) {
				cout << k.second << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}
