// Problem 8
// MemoryTree is used for the bruteforce solution of part 2
#include"../dep/MemoryTree.hpp"

// std libs
#include<algorithm>
#include<string>
#include<sstream>
#include<iostream>
#include<chrono>
#include<array>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<queue>
#include<stack>
#include<cmath>
#define ll long long
const ll inf = 1e17;
const int low_inf = 1e8;
using namespace std;

class Mat {
	vector<int> dat; 
public:
	int width, height;
	//
	Mat(int i, int j, int fill_val=0) : dat(i*j, fill_val) , width(i), height(j) {
	}
	void fill(int value) {
		for (auto& v : dat)
			v = value;
	}
	int& operator()(int i, int j) {
		return dat[i*width+j];
	}
	const int& operator()(int i, int j) const {
		return dat[i*width+j];
	}
};

struct Path {
	ll len;
	vector<pair<int,int>> points;
	Path(int points_res_len = 16) {
		points.reserve(points_res_len);
	}
	void print() {
		cout << "path:\n";
		for (const auto& pa : points) {
			cout << "\t" << pa.first << ", " << pa.second << "\n";
		}
	}
};

namespace part_1 {

	Path shortest(const Mat& mat) {
		Mat dp(mat.width, mat.height);
		Path path(mat.width + mat.height);
		for (int i = mat.width-1; i >= 0; i--) {
			for (int j = mat.height-1; j >= 0; j--) {
				auto min_adj = min(
					(i < dp.height-1 ? dp(i+1, j) : inf)
					, (j < dp.width -1 ? dp(i, j+1) : inf)
					);
				dp(i, j) = mat(i, j) + (min_adj==inf ? 0 : min_adj);
			}
		}
		int x=0, y=0;
		while(x != mat.width-1 || y != mat.height-1) {
			path.points.push_back({x, y});
			//
			auto e1 = (x < dp.height-1 ? dp(x+1, y) : inf);
			auto e2 = (y < dp.width -1 ? dp(x, y+1) : inf);
			if (e1 != inf || e2 != inf) {
				if (e1 < e2) {
					x++;
				} else {
					y++;
				}
			}
		}
		path.points.push_back({mat.width-1, mat.height-1});
		path.len = dp(0, 0);
		return path;
	}
	
}


inline int min(int a, int b, int c, int d) {
	return std::min(std::min(a, b), std::min(c, d));
}

namespace part_2 {

	class rec_util {
		const Mat& mat;
		Mat dp;
		int res = -1;
		MemoryTree<pair<int,int>> tree;
	public:
		int get_res() {
			return res;
		}
		Mat get_dp() {
			return dp;
		}

		rec_util(const Mat& mat) : mat(mat), dp(mat.width, mat.height, low_inf) {
			//res = rec_BruteForce(0, 0, -1);
			dp(mat.width-1, mat.height-1) = mat(mat.width-1, mat.height-1);
			algo();
		}

		inline int dp_get(int i, int j) {
			if (i < 0 || j < 0 || i >= dp.width || j >= dp.height) return low_inf;
			return dp(i, j);
		}
		
		void algo() {
			bool change;
			do {
				cout << "..\n";
				change = false;
				for (int i = mat.width-1; i >= 0; i--) {
					for (int j = mat.height-1; j >= 0; j--) {
						auto new_val = mat(i, j) +
								min(dp_get(i+1, j), dp_get(i, j+1), dp_get(i-1, j), dp_get(i, j-1));
						if (new_val < dp(i, j)) {
							dp(i, j) = new_val;
							change = true;
						}
					}
				}
			} while(change);
		}

		// Dont ever use this ;)
		int rec_BruteForce(int x, int y, int parId) {
			//cout << "::-> \n";
			if (x == mat.width-1 && y == mat.height-1) {
				//cout << "r: \n";
				return mat(mat.width-1, mat.height-1);
			}
			//cout << "1\n";
			if (tree.canBranchFind(parId, {x,y})) {
				//cout << "hey\n";
				return low_inf;
			}
			//cout << "2\n";
			if (x < 0 || x >= mat.width || y < 0 || y >= mat.height) {
				return low_inf;
			}
			//cout << "3\n";
			auto nodeId = tree.emplace_child(parId, {x,y});
			return mat(x, y) +
				min(
					rec_BruteForce(x+1, y, nodeId),
					rec_BruteForce(x, y+1, nodeId),
					rec_BruteForce(x-1, y, nodeId),
					rec_BruteForce(x, y-1, nodeId)
				);
		}
	};

	Path shortest(const Mat& mat) {
		rec_util util(mat);
		Mat dp = util.get_dp();
		// path construction from dp-mat
		Path path;
		int x=0, y=0;
		while(x != mat.width-1 || y != mat.height-1) {
			path.points.push_back({x, y});
			//
			auto e1 = (x < dp.height-1 ? dp(x+1, y) : low_inf);
			auto e2 = (y < dp.width -1 ? dp(x, y+1) : low_inf);
			auto e3 = (x > 0 ? dp(x-1, y) : low_inf);
			auto e4 = (y > 0 ? dp(x, y-1) : low_inf);
			if (e1 != low_inf || e2 != low_inf || e3 != low_inf || e4 != low_inf) {
				auto _min = min(e1, e2, e3, e4);
				if (_min == e1) {
					x++;
				} else if(_min == e2) {
					y++;
				} else if(_min == e3) {
					x--;
				} else {
					y--;
				}
			}
		}
		path.points.push_back({mat.width-1, mat.height-1});
		path.len = dp(0, 0);
		return path;
	}

}

int main() {
	// string input
	const int N = 5;
	const string str =
	"2  10 31 71 2  "
	"5  23 17 49 52 "
	"12 91 1  11 4  "
	"3  2  8  49 31 "
	"31 11 60 71 62 ";
	stringstream ss(str);
	
	// mat construction
	Mat mat(N, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			ss >> mat(i, j);
		} 
	} 

	// part 1)
	auto path = part_1::shortest(mat);
	std::cout << "Part 1, shortest path : " << path.len << "\n";
	path.print();

	cout << "-------------------\n";

	// part 2)
	path = part_2::shortest(mat);
	std::cout << "Part 2, shortest path : " << path.len << "\n";
	path.print();

}
