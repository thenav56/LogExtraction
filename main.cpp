#include <iostream>
#include <fstream>
#include <sstream>
#include "HMM.h"
#include "regex_key_value.h"

using namespace std;

typedef pair<int, string> T;

vector<T> tokenize(string s) {
	istringstream is(s);
	vector<T> res;
	string t;
	for (int i = 0; is >> t; ++i) {
		res.emplace_back(i, t);
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
vector<vector<T>> transformLogs(vector<vector<T>> & logs) {
	reg.readFromFile("regex.tl");
	vector<vector<T>> res;
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

int main(int cnt, char * args[])
{
	if(cnt<4){
		cout<<"Hidden Markov Model Implementation\n";
		cout<<"Usage: Program-name training-file tagging-file\n";
	} else{
		vector<vector<T>> ufile = read(args[1]);
		vector<vector<T>> tfile = read(args[2]);
		vector<vector<T>> logs = read(args[3]);
		vector<vector<T>> transformed = transformLogs(logs);
		HMM<T> hmm;
		/*for (auto i = transformed.begin(); i != transformed.end(); ++i) {
			for (auto j = i->begin(); j != i->end(); ++j) {
				cout<<j->first<<"\t"<<j->second<<"\n";
			}
		}*/
		hmm.Train(ufile, tfile);

		hmm.TagLogs(logs);

	}
}
