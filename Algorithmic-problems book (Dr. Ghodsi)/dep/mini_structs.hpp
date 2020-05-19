#pragma once
#include<iostream>
#include<vector>
#ifndef ll
	#define ll long long
#endif

struct Path2 {
	ll len;
	vector<pair<int,int>> points;
	Path2(int points_res_len = 16) {
		points.reserve(points_res_len);
	}
	void print() {
		cout << "path2:\n";
		for (const auto& pa : points) {
			cout << "\t" << pa.first << ", " << pa.second << "\n";
		}
	}
};

struct Path {
	ll len;
	vector<int> points;
	Path(const ll& len, const vector<int>& points) : len(len), points(points){}
	Path(int points_res_len = 16) {
		points.reserve(points_res_len);
	}
	void print() {
		cout << "path:\n";
		for (const auto& v : points) {
			cout << "\t" << v << "\n";
		}
	}
};
