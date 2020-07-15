#include<iostream>
#include<vector>
#include<unordered_set>
#include"Mat.hpp"
#include"state.hpp"
using namespace std;


class checker {
    Mat<char> mat;
    
    unordered_set<state, Hash> saved_states;
    void save(state s) {
        saved_states.insert(s);
    }

    struct pairProps {
        int k, dir; bool horizontal;
        pairProps(int k, int dir, bool horizontal) : k(k), dir(dir), horizontal(horizontal) {}
    };

    vector<pairProps> getPairs() {
        vector<pairProps> vec; 
        for (int k = 0; k < mat.size(); k++) {
            if (mat.canPlaceL(k, 1, false)) {
                vec.push_back(pairProps(k, 1, false));
            }
            if (mat.canPlaceL(k, -1, false)) {
                vec.push_back(pairProps(k, -1, false));
            }
            if (mat.canPlaceL(k, 1, true)) {
                vec.push_back(pairProps(k, 1, true));
            }
            if (mat.canPlaceL(k, -1, true)) {
                vec.push_back(pairProps(k, -1, true));
            }
            // we dont need more than this
        }
        return vec;
    }

    // calculates possible pairs given first one. k = firstPos
    void calc_pairs(int k, int firstDir, bool horizontal = false) {
        if (mat.canPlaceL(k, firstDir, horizontal)) {
            mat.placeL(k, firstDir, horizontal, 2);
            //if (horizontal)
            //cout << "\nH:\n";
                //mat.print<int>();
            auto pairs = getPairs();
            if (pairs.size() == 1) {
                //mat.print<int>();
                const auto& pairProps = pairs[0];
                mat.placeL(pairProps.k, pairProps.dir, pairProps.horizontal, 3);
                save(state(mat));
                mat.removeL(pairProps.k, pairProps.dir, pairProps.horizontal);
                //cout << "...\n";
            }
            mat.removeL(k, firstDir, horizontal);
                //mat.print<int>();
        }
    }

public:
    checker(int width, int height) : mat(width, height) {
    }

    void print() {
        cout << "count: " << saved_states.size() << '\n';
        for (auto& s : saved_states) {
            s.print();
        }
    }

    void check() {
        for (auto& s1 : saved_states) {
            int count = 0;
            for (auto& s2 : saved_states) {
                if (s1 == s2) count++;
            }
            if (count != 1) {
                throw "ERRR..............\n\n";
            }
        }
        cout << "No Problem\n";
    }

    void run() {
        for (int i = 0; i < mat.size(); i++) {
            mat(i) = 1;
            for (int j = i+1; j < mat.size(); j++) {
                mat(j) = 1;
                //
                for (int k = 0; k < mat.size(); k++) {
                    calc_pairs(k, 1);
                    calc_pairs(k, -1);
                    calc_pairs(k, 1, true);
                    calc_pairs(k, -1, true);
                }
                //
                mat(j) = 0;
            }
            mat(i) = 0;
        }
    }

};


int main() {
    checker c(4, 4);
    c.run();
    c.print();
}