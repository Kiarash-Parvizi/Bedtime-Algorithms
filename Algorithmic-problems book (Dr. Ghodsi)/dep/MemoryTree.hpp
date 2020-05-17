// Note: required c++11 or above 
#pragma once
#include<iostream>
#include<vector>
using namespace std;



template<typename T>

class MemoryTree {
	// PRIVATE
	// Node struct
	struct MemoryNode {
		T val;
		vector<int> childs;
		int parent;
		// constructor
		MemoryNode(int parent, T val) : val(val), parent(parent) {
		}
	};
	// data vec
	vector<MemoryNode> nodes;
	
public:
	MemoryTree(int res_size = 256) {
		nodes.reserve(res_size);
	}

	// parent_id<0 : adds new node directly to the root
	const int emplace_child(const int parent_id, const T child_val) {
		nodes.emplace_back(MemoryNode(parent_id, child_val));
		if (parent_id>=0)
			nodes[parent_id].childs.push_back(nodes.size()-1);
		return nodes.size()-1;
	}

	bool canBranchFind(const int leaf_id, const T val) const {
		int idx = leaf_id;
		while(idx >= 0) {
			const auto& node = nodes[idx];
			if (node.val == val) {
				return true;
			}
			//
			idx = node.parent;
		}
		return false;
	}
};


