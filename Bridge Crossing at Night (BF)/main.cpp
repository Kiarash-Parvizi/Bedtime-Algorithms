#include<bits/stdc++.h>
using namespace std; int n, i, t;
struct State {
    vector<vector<int>> B_History; vector<int> A, B; int time;
    State(vector<int> list) : time(0) { A = list; }
    void RECORD() { B_History.push_back(B); } void POPRECORD() { B_History.pop_back(); }
    void ADD_Time(int t) { time += t; }
};
struct H { vector<vector<int>> record; int time; H(State s) : time(s.time), record(s.B_History) { } };
vector<H> History;

void REC(State s) {
    for (int i = 0; i < s.A.size(); i++) {
        for (int j = i+1; j < s.A.size(); j++) {
            s.B.push_back(s.A[i]); s.B.push_back(s.A[j]); s.A.erase(s.A.begin()+j); s.A.erase(s.A.begin()+i);
            s.RECORD(); int t = max(s.B[s.B.size()-1], s.B[s.B.size()-2]); s.ADD_Time(t);
            if (!s.A.size()) { History.push_back(H(s)); goto FINAL; }
            // Choose(1, B.size)
            for (int a = 0; a < s.B.size(); a++) {
                s.A.push_back(s.B[a]); s.B.erase(s.B.begin()+a);
                s.RECORD(); s.ADD_Time(s.A[s.A.size()-1]);
                REC(s);
                s.ADD_Time(-s.A[s.A.size()-1]);
                s.B.insert(s.B.begin()+a, s.A[s.A.size()-1]); s.A.pop_back();
                s.POPRECORD();
            }
            FINAL:
            s.ADD_Time(-t);
            s.A.insert(s.A.begin()+i, s.B[s.B.size()-2]);
            s.A.insert(s.A.begin()+j, s.B[s.B.size()-1]);
            s.B.pop_back(); s.B.pop_back();
            s.POPRECORD();
        }
    }
}

bool CMP(H& a, H& b) { return a.time < b.time; }

int main() {
    vector<int> list = {1, 2, 5, 10}; // YOU CAN CHANGE THIS ***
    REC(State(list));
    sort(History.begin(), History.end(), CMP);
    // PRINT
    for (i = 0; i < History.size(); i++) {
        for (int j = 0; j < History[i].record.size(); j++) {
            cout << "{ ";
            for (int a = 0; a < History[i].record[j].size(); a++) { cout << History[i].record[j][a] << " "; }
            cout << " }\n";
        }
        cout << "time: " << History[i].time << "\n-------------------------------------------\n";
    }
}
