#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <list>

#undef DBG

const int SUPPORT = 3;


template <typename T>
struct FPTree {
	private:
		struct Node {
			std::vector<Node *> child;
			Node * parent;
			T key; //initializes itself 
			int count;
			Node () : parent(0), count(0) { }
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
		void insert_log(const std::vector<std::pair<int, T>> & log_data, bool conditional = 0) {
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
				nd->count += (conditional ? i.first : 1);
				cur = nd;
			}
		}
		void print(Node * nd, std::vector<std::pair<int, T>> res) {
			for (auto i : res) {
				std::cout << "[" << i.second << "=>" << i.first << "], ";
			}
			std::cout << "\n";
			for (Node * i : nd->child) {
				if (i) {
					res.emplace_back(i->count, i->key);
					print(i, res);
					res.pop_back();
				}
			}
		}
		//build conditional pattern base for given token
		std::vector<std::vector<std::pair<int, T>>> build_pattern_base(const T & token) {
			std::list<Node * > & tok_list = header[token];
			std::vector<std::vector<std::pair<int, T>>> res;
			for (auto & i : tok_list) {
				Node * cur = i;
				std::vector<std::pair<int, T>> prefix_path;
				cur = cur->parent; //skip "token" whose pattern base we are building
				while (cur->parent) {//repeat until we encounter the root 
					prefix_path.emplace_back(i->count, cur->key);
					cur = cur->parent;
				}
				reverse(prefix_path.begin(), prefix_path.end());
				if (!prefix_path.empty()) res.push_back(prefix_path);
			}
			return res;
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
		bool islinkedlist() const {//returns true if FP tree is a single path or linked list
			Node * cur = root;
			while (cur) {
				if (cur->child.size() > 1) return 0;
				cur = cur->child.empty() ? nullptr : cur->child[0];
			}
			return 1;
		}
		
		std::vector<std::vector<T>> mine() {
			if (!root || root->child.empty()) {
				return std::vector<std::vector<T>>();
			}
			std::vector<std::vector<T>> res;
			for (auto i : count) {
				if (i.second >= SUPPORT) {
					auto r = build_pattern_base(i.first);
					FPTree cond_fp_tree;
					for (auto & j : r) {
						cond_fp_tree.insert_log(j, true);
						for (auto & k : j) {
							cond_fp_tree.count[k.second] += k.first;
						}
					}
#ifdef DEBUG
					std::cout << "conditional fp tree for " << i.first << "\n";
					cond_fp_tree.traverse();
					std::cin.get();
#endif
					auto ptrns = cond_fp_tree.mine();
					ptrns.push_back(std::vector<T>());
#ifdef DBG
					std::cout << "patterns: conditional fp tree for " << i.first << "\n";
#endif
					for (auto & k : ptrns) {
						k.push_back(i.first);
						res.push_back(k);
#ifdef DBG
						for (auto j : k) std::cout << j << " ";
						std::cout << "\n";
#endif
					}
#ifdef DBG
					std::cin.get();
#endif
				}
			}
			return res;
		}
		void traverse() {
			if (root) print(root, std::vector<std::pair<int, T>>());
		}
		~FPTree() {
			delete root;
		}
};
