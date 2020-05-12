#include<iostream>
using namespace std;

int main() {
	string str = "RLLRL";
	const int en = str.size()-1;
	bool change;
	int counter = 0;
	do {
		change = false;
		for (int i = 0; i < en; i++) {
			if (str[i] == 'R' && str[i+1] == 'L') {
				str[i] = 'L';
				str[i+1] = 'R';
				i++; change = true;
			}
		}
		if (change) counter++;
	} while(change);
	//print
	cout << str << '\n';
	cout << counter << '\n';
}
