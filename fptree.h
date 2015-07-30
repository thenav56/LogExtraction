#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <list>

const int SUPPORT = 2;

template <typename T>
struct FPTree {
	private:
		struct Node {
			std::vector<Node *> child;
			Node * parent;
			T key; //initializes itself 
			int count;
			Node () : child(), parent(0), count(0) { }
			~Node() {
				for (Node * i : child) {
					delete i;
				}
			}
		};
		//members
		Node * root;
		std::map<T, int> count;
		std::map<T, std::list<Node *>> header; //table of linked list for each token

		//assumes that log is sorted according to the support count in descending
		//order and also the log file is clean in the sense that all tokens have
		//support count at least SUPPORT
		void insert_log(const std::vector<std::pair<int, T>> & log_data) {
			if (root == 0) root = new Node();
			Node * cur = root;
			for (auto & i : log_data) {
				Node * nd = 0;
				for (auto & j : cur->child) {
					if (j->key == i.second) {
						nd = j;
						break;
					}
				}
				if (nd == 0) {
					nd = new Node();
					nd->key = i.second;
					nd->parent = cur;
					header[nd->key].push_back(nd);
					cur->child.push_back(nd);
				}
				nd->count++;
				cur = nd;
			}
		}
		void print(Node * nd, std::vector<T> res) {
			bool leaf = 1;
			for (Node * i : nd->child) {
				if (i) {
					leaf = 0;
					res.push_back(i->key);
					print(i, res);
					res.pop_back();
				}
			}
			if (leaf) {
				for (auto i : res) {
					std::cout << "[" << i << "=>" << count[i] << "], ";
				}
				std::cout << "\n";
			}
		}
	public:
		FPTree() : root(0) { }
		void build(const std::vector<std::vector<T>> & logs) {
			for (auto & i : logs) {
				for (auto & j : i) count[j]++;
			}
			if (root) delete root, root = 0;
			for (auto & i : logs) {
				std::vector<std::pair<int, T>> log_data;
				for (auto & j : i) {
					if (count[j] >= SUPPORT) log_data.emplace_back(count[j], j);
				}
				std::sort(log_data.begin(), log_data.end(), std::greater<std::pair<int, T>>());
				insert_log(log_data);
			}
		}
		void traverse() {
			print(root, std::vector<T>());
		}
		~FPTree() {
			delete root;
		}
};
