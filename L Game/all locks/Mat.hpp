#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class Mat {
    int w, h;
    vector<T> vec;
public:
    Mat(int w, int h) : w(w), h(h), vec(w*h) {
    }

    int size() const {
        return vec.size();
    }

    template<class t>
    void print() const {
        for (int i = 0; i < vec.size(); i++) {
            if (i%w == 0) cout << '\n';
            cout << (t)vec[i] << ' ';
        }
        cout << '\n';
    }

    bool canPlaceL(int i, int dir, bool horizontal) {
        if (horizontal) {
            return ( (dir == 1 && i/w != h-1) || (dir == -1 && i/w != 0) ) && (
                !vec[i] && !vec[i+dir*w] &&
                ( i%w <= 1 ? ( !vec[i+1] && !vec[i+2] ) : ( !vec[i-1] && !vec[i-2] ) )
            );
        }
        return ( (dir == 1 && i%w != w-1) || (dir == -1 && i%w != 0) ) && (
            !vec[i] && !vec[i+dir] &&
            ( i/w <= 1 ? ( !vec[i+w] && !vec[i+2*w] ) : ( !vec[i-w] && !vec[i-2*w] ) )
        );
    }

    void placeL(int i, int dir, bool horizontal, int id) {
        if (horizontal) {
            vec[i] = id; vec[i+dir*w] = id;
            if (i%w <= 1) { vec[i+1] = id; vec[i+2] = id; } else { vec[i-1] = id; vec[i-2] = id; }
            return;
        }
        vec[i] = id; vec[i+dir] = id;
        if (i/w <= 1) { vec[i+w] = id; vec[i+2*w] = id; }
        else { vec[i-w] = id; vec[i-2*w] = id; }
    }

    void removeL(int i, int dir, bool horizontal) {
        if (horizontal) {
            vec[i] = 0; vec[i+dir*w] = 0;
            if (i%w <= 1) { vec[i+1] = 0; vec[i+2] = 0; } else { vec[i-1] = 0; vec[i-2] = 0; }
            return;
        }
        vec[i] = 0; vec[i+dir] = 0;
        if (i/w <= 1) { vec[i+w] = 0; vec[i+2*w] = 0; }
        else { vec[i-w] = 0; vec[i-2*w] = 0; }
    }

    T& operator () (int i, int j) {
        if (i < 0 || i > w || j < 0 || j > h) throw std::exception();
        return vec[j*w + i];
    }
    T& operator () (int i) {
        if (i < 0 || i > vec.size()) throw std::exception();
        return vec[i];
    }

    const T& operator () (int i, int j) const {
        if (i < 0 || i > w || j < 0 || j > h) throw std::exception();
        return vec[j*w + i];
    }
    const T& operator () (int i) const {
        if (i < 0 || i > vec.size()) throw std::exception();
        return vec[i];
    }
};