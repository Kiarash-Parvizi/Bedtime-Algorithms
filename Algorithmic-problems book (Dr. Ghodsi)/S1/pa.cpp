#include<iostream>
#include<vector>
#define ll long long
using namespace std;


int main() {
	vector<float> vec
	{10.5, -3.7, -4.2, -2.5, 3.2, -5.5,
	2.1, -1.1, 7.5, 0.3, -0.7, 5.7, -0.7,
	-0.2, 0.5, -5.2};
	double _max = 0;
	double _sum = 0;
	int s, ss, e, i=1;
	for (const auto& v : vec) {
		if (!_sum && v > 0) {
			s = i;
		}
		_sum += v;
		if (_sum > _max) {
			_max = _sum;
			e = i; ss = s;
		} else {
			if (_sum < 0)
				_sum = 0;
		}
		//
		i++;
	}
	// Output
	cout << _max << " -> range { " << ss << ", " << e << " }\n";
}
