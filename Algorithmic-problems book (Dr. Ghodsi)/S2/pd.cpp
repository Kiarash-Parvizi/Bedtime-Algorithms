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
	void add_edge(int s, int e) { s--; e--;
		nodes[s].childs.push_back(e);
		nodes[e].childs.push_back(s);
	}

	vector<vector<int>> connected_components() {
		// dfs structs
		vector<int> vec; vec.reserve(size);
		//
		vector<vector<int>> res;
		vector<bool> vised(size);
		for (int i = 0; i < size; i++) {
			if (!vised[i]) {
				res.emplace_back(vector<int>());
				res[res.size()-1].emplace_back(i+1);
				vised[i] = true;
				//dfs
				vec.push_back(i);
				while(vec.size()) {
					int id = vec[vec.size()-1];
					vec.pop_back();
					for (const auto c: nodes[id].childs) {
						if (!vised[c]) {
							vec.emplace_back(c);
							res[res.size()-1].emplace_back(c+1);
							vised[c] = true;
						}
					}
				}
			}
		}
		return res;
	}
};

int main() {
	const int n = 8;
	Graph<char> g(n);
	g.add_edge(1, 2);
	g.add_edge(5, 4);
	g.add_edge(5, 7);
	g.add_edge(5, 8);
	g.add_edge(1, 2);
	g.add_edge(1, 6);

	auto cc = g.connected_components();
	for (const auto& vek: cc) {
		cout << "component:\n";
		for (const auto& v: vek) {
			cout << v << ", ";
		}
		cout << "\n\n";
	}
}
