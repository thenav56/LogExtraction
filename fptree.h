#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <list>

//#define DBG

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
		const int SUPPORT; //support or threshold value for the algorithm
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
		void print(Node * nd, std::vector<std::pair<int, T>> & res) const {
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
		void build_pattern_base(const T & token, std::vector<std::vector<std::pair<int, T>>> & res) const {
			const std::list<Node * > & tok_list = header.find(token)->second;
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
		}

		//returns true if FP tree is a linked list
		bool isLinkedList() const {
			Node * cur = root;
			while (cur) {
				if (cur->child.size() > 1) return 0;
				cur = cur->child.empty() ? 0 : cur->child[0];
			}
			return 1;
		}
		void mine(std::vector<T> & pattern, std::vector<std::vector<T>> & pattern_bin) const {
			if (!root || root->child.empty()) return ;
			//for maximal frequent itemset
			if (isLinkedList()) {
				Node * cur = root;
				std::vector<T> p = pattern;
				while (cur) {
					if (count.find(cur->key)->second >= SUPPORT) p.push_back(cur->key);
					cur = cur->child.empty() ? 0 : cur->child[0];
				}
				pattern_bin.push_back(p);
				return ;
			}
			std::vector<std::vector<T>> res;
			for (auto i : count) {
				if (i.second >= SUPPORT) {
					std::vector<std::vector<std::pair<int, T>>> r;
					build_pattern_base(i.first, r);
					FPTree cond_fp_tree(SUPPORT);
					for (auto & j : r) {
						cond_fp_tree.insert_log(j, true);
						for (auto & k : j) {
							cond_fp_tree.count[k.second] += k.first;
						}
					}
#ifdef DBG
					std::cout << "conditional fp tree for " << i.first << "\n";
					cond_fp_tree.traverse();
					std::cin.get();
#endif
					pattern.push_back(i.first);
					pattern_bin.push_back(pattern);
					cond_fp_tree.mine(pattern, pattern_bin);
					pattern.pop_back();
				}
			}
		}
		void clearFPTree() {
			count.clear();
			header.clear();
			if (root) delete root, root = 0;
		}
	public:
		FPTree(int support) : root(0), SUPPORT(support) { }
		void build(const std::vector<std::vector<T>> & logs) {
			clearFPTree(); 
			for (auto & i : logs) {
				for (auto & j : i) count[j]++;
			}
			for (auto & i : logs) {
				std::vector<std::pair<int, T>> log_data;
				for (auto & j : i) {
					if (count[j] >= SUPPORT) log_data.emplace_back(count[j], j);
				}
				std::sort(log_data.begin(), log_data.end(), std::greater<std::pair<int, T>>());
				insert_log(log_data);
			}
		}
		//returns all frequent itemsets in pattern_bin
		void mine(std::vector<std::vector<T>> & pattern_bin) const {
			std::vector<T> P;
			mine(P, pattern_bin);
		}
		void traverse() const {
			std::vector<std::pair<int, T>> P;
			if (root) print(root, P);
		}
		~FPTree() {
			delete root;
		}
};
