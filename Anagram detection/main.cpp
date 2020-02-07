#include<bits/stdc++.h>
using namespace std; int n, i, t;
vector<string> dic = {"ate", "tea", "ate", "job", "boj", "aet", "eta", "kia"};
map<string, int> MAP;

int main() {
    string s;
    for (i = 0; i < dic.size(); i++) { s = dic[i]; sort(s.begin(), s.end()); MAP[s]++; }
    // PRINT
    for (auto it = MAP.begin(); it != MAP.end(); it++) { cout << "[" << it->first << "] : " << it->second << '\n'; }
}
