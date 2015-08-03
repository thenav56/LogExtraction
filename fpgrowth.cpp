#include <iostream>
#include "fptree.h"

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

int main(int cnt, char * args[]) {
	if (cnt < 3) {
		cout << "FP GROWTH ALGORITHM IMPLEMENTATION\n";
		cout << "Usage: program_name log_file support_value\n";
	} else {
		int s = atoi(args[2]);
		FPTree<T> tree(s);
		//consider the position of token in the line
		tree.build(read(args[1]));
		std::vector<std::vector<T>> r;
		clock_t t = clock();
		tree.mine(r);
		cout << "Time: " << double(clock() - t) / CLOCKS_PER_SEC << "\n";
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
