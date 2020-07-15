#include<iostream>
#include<vector>
#include"Mat.hpp"
using namespace std;

struct state {
    Mat<char> mat;
    state(Mat<char> s) : mat(s) {}

    void print() const {
        mat.print<int>();
    }

    long long id() const {
        long long id = 0;
        long long z = 1;
        for (int i = 0; i < mat.size(); i++) {
            id += z * mat(i);
            z *= 4;
        }
        //cout << id << '\n';
        return id;
    }

    bool operator == (const state& o) const {
        return id() == o.id();
    } 
};
struct Hash { 
    // id is returned as hash function 
    size_t operator()(const state& o) const { 
        return o.id(); 
    } 
};