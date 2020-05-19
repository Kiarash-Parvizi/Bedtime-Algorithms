// Problem 0xe
#include"../dep/MemoryTree.hpp"
#include"../dep/string_tools.hpp"
#include"../dep/mini_structs.hpp"

#include<iostream>
#include<vector>
using namespace std;


template<class T>
class Graph {
	struct Node {
		T val;
		vector<int> childs;
	};
	vector<Node> nodes;
	int size;
public:
	Graph(int size) : size(size), nodes(size) {
	}
	void set_node(int id, const T& val) {
	}
	void add_edge(int s, int e) {
		nodes[s].childs.push_back(e);
		nodes[e].childs.push_back(s);
	}
	Path shortest_loop() {
		MemoryTree<int> tree; tree.emplace_child(-1, 1);
		vector<pair<int,int>> vec; // nId, node
		vec.push_back({0, 0});
		int branch_id = -1, fin_id=-1, min_loop=size+1;
		//dfs
		while(vec.size()) {
			auto top = vec[vec.size()-1];
			vec.pop_back();
			auto& node = nodes[top.second];
			for (const auto c: node.childs) {
				auto loop_len = tree.branchFind(top.first, c+1);
				if (loop_len != -1) {
					if (loop_len != 1) {
						//cout << "::" << loop_len << '\n';
						if (loop_len < min_loop) {
							min_loop = loop_len;
							fin_id = c+1; branch_id = top.first;
						}
					}
				} else {
					auto id = tree.emplace_child(top.first, c+1);
					vec.push_back({id, c});
				}
			}
		}
		auto branch = tree.get_branch_to(branch_id, fin_id);
		return {min_loop+1, branch};
	}
};

int main() {
	string str =
	" 1"
	" 1 1"
	" 0 1 1"
	" 1 0 1 0"
	" 1 1 0 0 0"
	" 0 0 0 1 1 1";
	//" 1"
	//" 0 1"
	//" 0 0 1"
	//" 1 0 0 1"
	//" 1 0 0 0 0"
	//" 0 1 0 0 0 0"
	//" 0 0 1 0 0 1 0"
	//" 0 0 0 1 0 1 1 0"
	//" 0 0 0 0 1 0 1 1 0";
	//const int n = 10;
	const int n = 7;
	auto edges = Util::lmat_to_edges(str, n);
	//
	Graph<char> g(n);
	for (const auto& v : edges) {
		//cout << "edge: " << v.first << ", " << v.second << '\n';
		g.add_edge(v.first, v.second);
	}
	// custom edges:
		//g.add_edge(0, 1);
		//g.add_edge(0, 2);
		//g.add_edge(0, 3);
		//g.add_edge(1, 4);
		//g.add_edge(2, 5);
		//g.add_edge(3, 6);
		//g.add_edge(4, 5);
	//
	auto path = g.shortest_loop();
	cout << "path len: " << path.len << '\n';
	path.print();
}
