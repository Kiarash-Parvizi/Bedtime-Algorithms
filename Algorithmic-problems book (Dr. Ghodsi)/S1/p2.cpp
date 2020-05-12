#include<iostream>
#include<vector>
#define ll long long
using namespace std;

namespace subseq {

	void print_subseqs(int n, int k) {
		if (k < 1 || k > n) return;
		vector<int> vec(k); // (place, iter)
		for (int i = 1; i <= k; i++) { vec[i-1] = i; }
		//Algo
		int control = k-1;
		ll count = 0;
		bool upward = false;
		while(control >= 0) {
			if (control == k-1) {
				vec[control] = vec[control-(control?1:0)]+1;
				for (; vec[control] <= n; vec[control]++) {
						cout << "( ";
						for (const auto& v : vec) cout << v << " ";
						cout << ")\n";
						count++;
				}
				control--;
				upward = false;
			}
			else {
				if (!upward && vec[control] == n-(k-1-control)) {
					control--;
					upward = false;
				}
				else {
					if (upward)
						vec[control] = vec[control-1]+1;
					else
						vec[control]++;
					control++;
					upward = true;
				}
			}
		}
		cout << "count: " << count << '\n';
	}
	
}

int main() {
	cout << "\nss(7, 3):\n";
	subseq::print_subseqs(7, 3);
	//crazy one
	//cout << "\nss(17, 8):\n";
	//subseq::print_subseqs(17, 8);
}
