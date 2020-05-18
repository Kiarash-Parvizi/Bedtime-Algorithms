// problem 0xc
#include"../dep/MemoryTree.hpp"

#include<algorithm>
#include<iostream>
#include<vector>
#include<cmath>
#define ll long long
using namespace std;

struct Pos {
	int x, y;
	bool operator==(const Pos& o) const {
		return x==o.x && y==o.y;
	}
};

struct Path {
	vector<Pos> points; 
	ll cost;
};

class Mat {
	vector<int> dat; 
public:
	int width, height;
	//
	Mat(const vector<int>& v, int i, int j) : dat(v), width(i), height(j) {}
	Mat(int i, int j, int fill_val=0) : dat(i*j, fill_val) , width(i), height(j) {
	}
	int& operator()(int i, int j) {
		return dat[i+j*width];
	}
	const int& operator()(int i, int j) const {
		return dat[i+j*width];
	}
};


class bf_util {
	MemoryTree<Pos> tree;
	Mat mat;
	Pos s, e;
	vector<Path> paths;
public:
	bf_util(const Mat& mat, const Pos& s, const Pos& e) : mat(mat), s(s), e(e) {
		rec(s, -1);
	}

	inline bool canGo(const Pos& pos) {
		if (pos.x >= mat.width || pos.x < 0 || pos.y >= mat.height || pos.y < 0)
			return false;
		return !mat(pos.x, pos.y);
	}

	void save_branch(const int nId) {
		paths.push_back({tree.get_branch(nId), -1});
	}

	vector<Path> get_paths() {
		return paths;
	}

	void rec(Pos pos, const int nId) {
		if (pos == e) {
			auto id = tree.emplace_child(nId, pos);
			save_branch(id);
			return;
		}
		if (tree.canBranchFind(nId, pos)) {
			return;
		}
		auto id = tree.emplace_child(nId, pos);
		for (int x = -2; x < 3; x++) {
			if (!x) continue;
			for (int y = -2; y < 3; y++) {
				if (!y) continue;
				if (abs(y) == abs(x)) continue;
				//
				Pos nPos = {pos.x+x,pos.y+y};
				if (canGo(nPos)) {
					rec(nPos, id);
				}
			}
		}
		tree.remove(id);
	}
};

int main() {
	// input
	const int n = 6;
	Mat mat({
		1, 0, 0, 1, 0, 0,
		0, 1, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 1,
		0, 0, 1, 0, 1, 0,
		0, 0, 1, 0, 0, 1,
		0, 0, 0, 0, 1, 0
	}, n, n);
	Pos s{5, 1};
	Pos e{1, 5};
	// code
	bf_util util(mat, s, e);
	auto paths = util.get_paths();
	// sort
	sort(paths.begin(), paths.end(), [](const Path& a, const Path& b){ return a.points.size()<b.points.size(); });
	// Print
	cout << "Total number of paths: " << paths.size() << '\n';
	for (const auto& p : paths) {
		cout << "Path:\n";
		for (const auto& v: p.points) {
			cout << v.y+1 << ", " << v.x+1 << '\n';
		}
		cout << "\n\n";
	}
}
