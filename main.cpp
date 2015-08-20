#include <iostream>
#include "include/fptree.h"
#include "include/cluster.h"
#include "include/regex_key_value.h"

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
	loadRegexTemplate("regex.tl");
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

int main(int cnt, char * args[]) {
	if (cnt < 3) {
		cout << "FP GROWTH ALGORITHM IMPLEMENTATION\n";
		cout << "Usage: program_name log_file support_value\n";
	} else {
		int s = atoi(args[2]);
		FPTree<T> tree(s);
		Cluster<T> data;
		std::vector<std::vector<T>> original = read(args[1]);
		std::vector<std::vector<T>> transformed = transformLogs(original);
		//consider the position of token in the line
		tree.build(transformed);
		std::vector<std::vector<T>> r;
		clock_t t = clock();
		tree.mine(r);
		std::cout<<"Initial pattern no: "<<r.size()<<"\n";
		data.AssociatePatterns(transformed, r);
		cout << "Time: " << double(clock() - t) / CLOCKS_PER_SEC << "\n";
		data.DisplayCluster(original, transformed, r, reg);
	}
	return 0;
}
