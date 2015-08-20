#include <iostream>
#include <fstream>
#include <sstream>
#include "HMM.h"

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

int main(int cnt, char * args[])
{
	if(cnt<3){
		cout<<"Hidden Markov Model Implementation\n";
		cout<<"Usage: Program-name training-file tagging-file\n";
	} else{
		vector<vector<T>> Tfile = read(args[1]);
		vector<vector<T>> logs = read(args[2]);
		HMM<T> hmm;
		hmm.Train(Tfile);
	}
}
