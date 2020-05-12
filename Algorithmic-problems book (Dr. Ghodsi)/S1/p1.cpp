#include<iostream>
using namespace std;

int main() {
	const int range = 1001;
	int* vec = new int[range];
	vec[1] = 1;
	vec[2] = 2;
	int p = 1;
	for (int i = 1; i < range; i++) {
		for (int j = 0; j < vec[i]; j++) {
			if (p >= range) goto out;
			vec[p] = i;
			p++;
		}
	}
	out:
	// print
	for (int i = 1; i < range; i++) {
		cout << i << ": " << vec[i] << '\n';
	}
}
