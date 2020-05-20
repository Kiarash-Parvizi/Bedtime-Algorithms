// Problem 0x10 and 0x11
#include"../dep/string_tools.hpp"

#include<iostream>
#include<vector>
#include<algorithm>
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
	vector<int> get_cuttingNodes() {
		vector<pair<int,int>> vec; // pathLen, nodeId
		vector<bool> isCuttingNode(size);
		for (int i = 0; i < size; i++) {
			if (nodes[i].childs.size() < 2) {
				continue;
			}
			vec.clear();
			int chId = nodes[i].childs[1];
			vec.push_back({0, chId});
			vector<bool> vised(size); vised[i] = true; vised[chId] = true;
			int counter = 1;
			//dfs
			while(vec.size()) {
				auto top = vec[vec.size()-1];
				vec.pop_back();
				auto& node = nodes[top.second];
				counter++;
				for (const auto c: node.childs) {
					if(!vised[c]) {
						vised[c] = true;
						vec.push_back({top.first+1, c});
					}
				}
			}
			if(counter!=size) {
				isCuttingNode[i] = true;
			}
		}
		vector<int> res;
		for (int i = 0; i < size; i++) {
			if(isCuttingNode[i] && nodes[i].childs.size() > 1) {
				res.emplace_back(i);
			}
		}
		return res;
	}

	vector<pair<int,int>> get_cuttingEdges(vector<int> cuttingNodes) {
		int idx = 0;
		for (const auto& node: nodes) {
			if(node.childs.size()==1) {
				cuttingNodes.push_back(idx);
			}
			idx++;
		}
		//
		vector<pair<int,int>> res;
		for (int i = 0; i < cuttingNodes.size(); i++) {
			for (int j = i+1; j < cuttingNodes.size(); j++) {
				auto& adj = nodes[cuttingNodes[i]].childs;
				if(find(adj.begin(), adj.end(), cuttingNodes[j]) != adj.end()) {
					res.push_back({cuttingNodes[i], cuttingNodes[j]});
				}
			}
		}
		return res;
	}
};

int main() {
	string str =
	" 1"
	" 1 1"
	" 0 1 1"
	" 0 1 0 1"
	" 0 0 0 0 0"
	" 0 0 0 0 0 1"
	" 1 0 0 0 0 1 1";
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
	const int n = 8;
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
	auto cuttingNodes = g.get_cuttingNodes();
	cout << "Cutting Nodes:\n";
	for (const auto v : cuttingNodes) {
		cout << "\t" << v+1 << '\n';
	}

	cout << "\nCutting Edges:\n";
	auto cuttingEdges = g.get_cuttingEdges(cuttingNodes);

	for (const auto& ed: cuttingEdges) {
		cout << "edge(" << ed.first+1 << ", " << ed.second+1 << ")\n";
	}
}
