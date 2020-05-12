#include<iostream>
#include<vector>
#include<cmath>
#define ll long long
using namespace std;

int F(int k) {
	int b_pow = 0;
	int i = 1;
	for (int p_val = 2; p_val <= k; p_val=p_val<<1) {
		if (k % p_val == 0) {
			b_pow = i;
		}
		i++;
	}
	return b_pow+1;
}

vector<int> gen_F_vec(int n) {
	vector<int> res(n);
	for (int i = 1; i <= n; i++) {
		res[i-1] = F(i);
	}
	return res;
}

vector<int> match_pat(vector<int> vec, vector<int> pat) {
 	vector<int> res; res.reserve(pat.size());
	if (!pat.size())
		return res;

	int j = 0; // pat-vec ptr
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == pat[j]) {
			res.emplace_back(i+1);
			j++;
			if (j == pat.size()) break;
		}
	}
	return res;
}

int main() {
	const int n = 5;
	const vector<int> per{3, 5, 4, 1, 2};
	
	//gen vec
	auto f_vec = gen_F_vec(pow(2, n)-1);
	auto ind_vec = match_pat(f_vec, per);
	//print
	//1
	for (const auto& v : f_vec) {
		cout << v << " ";
	} cout << '\n';
	//2
	for (const auto& v : ind_vec) {
		cout << v << " ";
	} cout << '\n';
}
