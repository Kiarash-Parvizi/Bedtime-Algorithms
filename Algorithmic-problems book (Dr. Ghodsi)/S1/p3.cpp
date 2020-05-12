#include<iostream>
#include<vector>
#define ll long long
using namespace std;

vector<ll> fac_base;
void init() {
	ll c = 1;
	for (ll i = 1; i < 19; i++) {
		c *= i;
		fac_base.emplace_back(c);
	}
}
vector<int> to_fac_base(ll num) {
	vector<int> res(fac_base.size());
	for (int i = res.size()-1; i >=0; i--) {
		if (num >= fac_base[i]) {
			res[i] = num/fac_base[i];
			num %= fac_base[i];
		}
	}
	return res;
}

void trim(vector<int>& vec) {
	int i = vec.size()-1;
	for (; vec[i]==0 && i >= 0; i--) {}
	if (i)
		vec.erase(vec.begin()+i+1, vec.end());
}

void print(const vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) cout << fac_base[i] << "\t";
	cout << '\n';
	for (const auto& v : vec) cout << v << "\t";
	cout << "\n";
}

int main() {
	init();
	//
	ll num = 200;
	auto vec = to_fac_base(num);
	trim(vec);
	print(vec);
}
