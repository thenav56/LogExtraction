#include <iostream>
#include "fptree.h"

using namespace std;
vector<string> 
tokenize(string s) {
	istringstream is(s);
	vector<string> res;
	string t;
	for (int i = 0; is >> t; ++i) {
		res.push_back(t);
	}
	return res;
}

vector<vector<string>> 
read(const char * file_name) {
	ifstream file(file_name);
	string s;
	vector<vector<string>> res;
	while (getline(file, s)) {
		res.push_back(tokenize(s));
	}
	return res;
}

int main(int cnt, char * args[]) {
	if (cnt < 2) {
		cout << "fptree build test\n";
		cout << "Usage: program_name log_file\n";
	} else {
		FPTree<string> tree;
		tree.build(read(args[1]));
		tree.traverse();
	}
	return 0;
}

