//Problem 0xb
#include"../dep/MemoryTree.hpp"
#include<iostream>
#include<vector>
#include<cmath>
#define ll long long
using namespace std;
struct Pos {
	int x, y;
	bool operator==(const Pos& o) const {
		return abs(o.x-x)==abs(o.y-y) || x==o.x;
	}
};

class rec_util {
	MemoryTree<Pos> tree;
	vector<string> paths;
	int w, h;
public:
	rec_util(int w, int h) : w(w), h(h) {
		rec(0, -1);
	}

	void save_path(const int nodeId) {
		auto path = tree.get_branch(nodeId);
		string str(w*h, '.');
		for (const auto& v : path) {
			str[v.x+v.y*w] = 'Q';
		}
		paths.push_back(str);
	}

	void print_paths() {
		cout << "Paths:\n";
		cout << "count: " << paths.size() << "\n";
		for (const auto& s : paths) {
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					cout << s[i*w+j] << ' ';
				}
				cout << '\n';
			}
			cout << "\n\n";
		}
	}

	void rec(int y, const int nId) {
		if(y == h) {
			save_path(nId);
			return;
		}
		for (int i = 0; i < w; i++) {
			if (!tree.canBranchFind(nId, {i, y})) {
				auto id = tree.emplace_child(nId, {i,y});
				rec(y+1, id);
				tree.remove(id);
			}
		}
	}
};

int main() {
	const int w = 8, h = 8;
	rec_util util(w, h);
	util.print_paths();
	//cout << "Done\n";
	//cin.get();
}


