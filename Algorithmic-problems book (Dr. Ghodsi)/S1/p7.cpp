#include<iostream>
#include<vector>
#define ll long long
using namespace std;

class graph {
	//node
	struct node {
		int val;
		vector<int> adjs;
		int par = 0;
	public:
		void add_par(int v) {
			par+=v;
		}
		void remove_childs(vector<node>& nodes) {
			for(const auto v : adjs) {
				nodes[v].add_par(-1);
			}
			adjs.clear();
		}
	};
	vector<node> nodes;
public:
	graph(int size) : nodes(size) {
	}
	void add_dir_edge(int s, int e) {
		nodes[s].adjs.push_back(e);
		nodes[e].add_par(1);
	}
	void set_val(int i, int v) {
		nodes[i].val = v;
	}
	//TopoSort -> not a good implementation. it just works
	vector<int> topo_sort() {
		vector<int> res;
		vector<bool> vised(nodes.size(), false);
		while (res.size() != nodes.size()) {
			for (int i = 0; i < nodes.size(); i++) {
				if (vised[i]) continue;
				if (nodes[i].par==0) {
					res.push_back(nodes[i].val);
					nodes[i].remove_childs(nodes);
					vised[i]=true;
				}
			}
		}
		return res;
	}
};

int main() {
	const vector<int> input{25, 14, 100, 7, 9};
	const int n = input.size();
	//
	graph g(n);
	for (int i = 0; i < n; i++) {
		//node val
		g.set_val(i, input[i]);
		//
		int p = input[i]%n;
		for (; p != i; p=(p+1)%n) {
			g.add_dir_edge(p, i);
		}
	}
	auto tSorted = g.topo_sort();
	//print
	for (const auto& v : tSorted) {
		cout << v << " ";
	}	cout << '\n';
}
