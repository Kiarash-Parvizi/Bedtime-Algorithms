#pragma once
#include<string>
#include<sstream>
#include<vector>

namespace Util {

	// Graphs
	std::vector<std::pair<int,int>> lmat_to_edges(const std::string& str, int n) {
		std::stringstream ss(str);
		std::vector<std::pair<int,int>> res;
		int i, j, v;
		for (i = 1; i < n; i++) {
			for (j = 0; j < i; j++) {
				ss >> v;
				if (v) {
					res.push_back({i,j});
				}
			}
		}
		return res;
	}

    // Splitter
    const std::vector<std::string>& split(const std::string& str) {
        static int s, e; s = 0; e = 0;
        static std::vector<std::string> vec;
        vec.clear();
        while(s < str.size()) {
            while(s < str.size() && str[s]==' ') { s++; } e = s;
            while(e < str.size() && str[e]!=' ') { e++; }
            if (e != s)
                vec.emplace_back(str.substr(s, e-s));
            s = e+1;
        }
        return vec;
    }

    const std::vector<double> string_to_double_array(const std::string& str) {
        static int s, e; s = 0;
        while(str[s] != '[') { s++; } s++; e = s+1;
        while(str[e] != ']') { e++; }
        auto subs = split(str.substr(s, e-s));
        std::vector<double> vec;
        if (!subs.size()) {
            return vec;
        }
        for (const auto& v : subs) {
            vec.emplace_back(std::stod(v));
        }
        return vec;
    }

    void to_lower(std::string& str) {
        static const char dif = 'a'-'A';
        for(auto& c : str) {
            if (c >= 'A' && c <= 'Z') {
                c += dif;
            }
        }
    }

}
