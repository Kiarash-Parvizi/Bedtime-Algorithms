#include<iostream>
#include<vector>
#define ll long long
using namespace std;

class Solver {
const ll M = 1e9+7;
public:
	Solver(ll max) {
		calc_f(max);
		calc_g(max);
	}
	ll solve_for(int n) {
		return G(n);
	}
private:
	vector<ll> f;
	void calc_f(int n) {
		if (n < 3) throw "calc_f err";
		f = vector<ll>(n+1); f[0] = 1; f[1] = 1; f[2] = 2;
		for (int i = 3; i <= n; i++) {
			f[i] = (f[i-1] + f[i-2] + f[i-3]) % M;
		}
	}
	
	vector<ll> g;
	void calc_g(int n) {
		if (n < 3) throw "calc_g err";
		g = vector<ll>(n+1);
		g[0] = 1;
		auto calc = [this](int i) {
			ll res = 0;
			for (int k = 0; k <= i; k++) {
				ll f_r = f[i-k];
				res = (res + ((f_r*f_r)%M) * (k-1 < 0 ? 1 : g[k-1]) ) % M;
			}
			return res;
		};
		for (int i = 1; i <= n; i++) {
			g[i] = calc(i);
		}
	}
	ll G(int i) {
		if (i < 0) throw "G func err";
		return g[i];
	}
};

int main() {
	Solver solver(1e3);
	//
	for (int i = 1; i <= 30; i++)
	cout << "g(" << i << ") = " << solver.solve_for(i) << '\n';
}
