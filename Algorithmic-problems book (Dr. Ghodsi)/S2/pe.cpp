// Problem 0xe
#include"../dep/MemoryTree.hpp"
#include"../dep/string_tools.hpp"
#include"../dep/mini_structs.hpp"

#include<iostream>
#include<vector>
#include<deque>
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
	Path shortest_path(int s, int e) {
		MemoryTree<int> tree; tree.emplace_child(-1, s+1);
		deque<pair<int,int>> vec; // nId, node
		vec.push_back({0, s});
		vector<bool> vised(size);
		int branch_id = -1;
		//bfs
		while(vec.size()) {
			auto v2 = vec.back(); vec.pop_back();
			auto& node = nodes[v2.second];
			for (const auto& c: node.childs) {
				if (!vised[c]) {
					auto id = tree.emplace_child(v2.first, c+1);
					if (c == e) {
						branch_id = id;
						goto end;
					}
					vec.push_front({id, c});
				}
			}
		}
	end:
		auto branch = tree.get_branch(branch_id);
		return {(ll)branch.size(), branch};
	}
};

int main() {
	string str =
	" 1"
	" 0 1"
	" 0 0 1"
	" 1 0 0 1"
	" 1 0 0 0 0"
	" 0 1 0 0 0 0"
	" 0 0 1 0 0 1 0"
	" 0 0 0 1 0 1 1 0"
	" 0 0 0 0 1 0 1 1 0";
	const int n = 10, s = 5, e = 7;
	auto edges = Util::lmat_to_edges(str, n);
	//
	Graph<char> g(n);
	for (const auto& v : edges) g.add_edge(v.first, v.second);
	//
	auto path = g.shortest_path(s-1, e-1);
	cout << "path len: " << path.points.size()-1 << '\n';
	path.print();
}
