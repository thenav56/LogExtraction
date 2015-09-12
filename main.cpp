#include <iostream>
#include <fstream>
#include <sstream>
#include "include/HMM.h"
#include "include/regex_key_value.h"
#include "include/fptree.h"
#include "include/cluster.h"
#include "include/Analyze.h"

using namespace std;

typedef pair<int, string> T;

vector<T> tokenize(string s) {
	istringstream is(s);
	vector<T> res;
	string t;
	for (int i = 0; is >> t; ++i) {
		res.push_back(make_pair(i, t));
	}
	return res;
}

vector<vector<T>>
read(const char * file_name) {
	ifstream file(file_name);
	string s;
	vector<vector<T>> res;
	while (getline(file, s)) {
		res.push_back(tokenize(s));
	}
	return res;
}

regex_key_value reg;
void loadRegexTemplate(const string & file) {
	ifstream f(file);
	string a, b;
	while (getline(f, a) && getline(f, b)) {
		reg.add(a, b);
	}
}

vector<vector<T>> transformLogs(const vector<vector<T>> & logs) {
	vector<vector<T>> res;
	loadRegexTemplate("regex.tl");
	for (auto & i : logs) {
		res.push_back(vector<T>());
		for (auto & j : i) {
			pair<int, string> p = reg.doRegex(j.second);
			if (p.first == -1) {
				res.back().emplace_back(j.first, "-1 " + j.second);
			} else {
				res.back().emplace_back(j.first, std::to_string(p.first));
			}
		}
	}
	return res;
}

vector<vector<T>> transform2(const vector<vector<T>> & logs) {
	vector<vector<T>> res;
	for (auto & i : logs) {
		res.push_back(vector<T>());
		for (int j = 0; j < (int)i.size(); ++j) {
			res.back().emplace_back(j, std::to_string(i[j].first));
		}
	}
	return res;
}
int main(int cnt, char * args[]) {
	if(cnt <= 4){
		cout<<"Minor Project\n";
		cout<<"Usage: Program-name untagged tagged logs support\n";
	} else{
		vector<vector<T>> ufile = read(args[1]);
		vector<vector<T>> tfile = read(args[2]);
		vector<vector<T>> logs = read(args[3]);
		HMM<T> hmm;
		/*for (auto i = transformed.begin(); i != transformed.end(); ++i) {
		  for (auto j = i->begin(); j != i->end(); ++j) {
		  cout<<j->first<<"\t"<<j->second<<"\n";
		  }
		  }*/
		hmm.Train(ufile, tfile);
		map<int, string> tagcodemap;
		vector<vector<T>> taglist = hmm.TagLogs(logs, tagcodemap);
		vector<vector<T>> transformed = transform2(taglist);		
		//FP GROWTH PART FOR CLUSTERING after classification
		int s = atoi(args[4]);
		FPTree<T> tree(s);
		//consider the position of token in the line
		tree.build(transformed);
		std::vector<std::vector<T>> r;
		clock_t t = clock();
		tree.mine(r);
		std::cout<<"Initial pattern no: "<<r.size()<<"\n";
		Cluster<T> data;
		data.AssociatePatterns(transformed, r);
		cout << "Time: " << double(clock() - t) / CLOCKS_PER_SEC << "\n";
		data.DisplayCluster(logs, transformed, r, tagcodemap);
		Analyze<T> analyze;
		vector<vector<T>> manual = read("manual");
		cout<<"\n"<<analyze.Efficiency(taglist, manual);
	}
	return 0;
}
