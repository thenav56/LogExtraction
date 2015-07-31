#include <iostream>
#include "fptree.h"

using namespace std;

vector<pair<int, string>> 
tokenize(string s) {
	istringstream is(s);
	vector<pair<int, string>> res;
	string t;
	for (int i = 0; is >> t; ++i) {
		res.emplace_back(i, t);
	}
	return res;
}

vector<vector<pair<int, string>>> 
read(const char * file_name) {
	ifstream file(file_name);
	string s;
	vector<vector<pair<int, string>>> res;
	while (getline(file, s)) {
		res.push_back(tokenize(s));
	}
	return res;
}

int main(int cnt, char * args[]) {
	if (cnt < 3) {
		cout << "FP GROWTH ALGORITHM IMPLEMENTATION\n";
		cout << "Usage: program_name log_file support_value\n";
	} else {
		int s = atoi(args[2]);
		FPTree<pair<int, string>> tree(s);
		//consider the position of token in the line
		tree.build(read(args[1]));
		//tree.traverse();
		auto r = tree.mine();
		cout << "Frequent patterns: " << r.size() << "\n";
		for (auto i : r) {
			for (auto j : i) {
				cout << j.second << " ";
			}
			cout << "\n";
		}
	}
	return 0;
}

