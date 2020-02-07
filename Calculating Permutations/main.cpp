#include<bits/stdc++.h>
using namespace std; int n, i, t; vector<vector<int>> vecBuffer;
namespace Printer {
    void vector(vector<int> vec) {
        cout << "{ "; for (int i = 0; i < vec.size(); i++) { cout << vec[i] << " "; } cout << "}\n";
    }
    void vectorVector() {
        for (int a = 0; a < vecBuffer.size(); a++) {
            cout << "{ "; for (int i = 0; i < vecBuffer[a].size(); i++) { cout << vecBuffer[a][i] << " "; } cout << "}\n";
        }
    }
}

void P(vector<int>& vec, vector<int>& res, vector<bool>& check, int stage) {
    if (stage == vec.size()) {
        // RETURN
        vecBuffer.push_back(*(new vector<int>(res)));
    }
    for (int i = 0; i < vec.size(); i++) {
        if (check[i]) {
            check[i] = false; res.push_back(vec[i]);
            P(vec, res, check, stage+1);
            check[i] = true;  res.pop_back();
        }
    }
}

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};
    P(vec, *(new vector<int>()), *(new vector<bool>(vec.size(), 1)), 0); Printer::vector(vec); Printer::vectorVector();
}
