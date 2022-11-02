#pragma once
#include "Header.h"


class node
{
public:
	string hash;
	struct node* left;
	struct node* right;
	node() { left = NULL; right = NULL; hash = ""; };
};
class MerkleTree
{
public:
	vector <node> tree;

private:
	node newNode(node* left, node* right, string hash) {
		SHA256 sha256;
		node N;
		if ((left == NULL) && (right == NULL)) N.hash = hash; 
		else N.hash = sha256(left->hash + right->hash);
		N.left = left;
		N.right = right;
		return N;
	}
public:
	MerkleTree(vector <Transaction> T) {
		vector <node> nodes;
		if (T.size() % 2 != 0) {
			T.push_back(T[T.size() - 1]);
		}
		for (auto a : T) {
			node n = newNode(NULL, NULL, a.getId());
			nodes.push_back(n);
		}
		for (int i = 0; i < (T.size() / 2); i++) {
			vector <node> level;
			if (nodes.size() % 2 != 0) {
				nodes.push_back(nodes[nodes.size() - 1]);
			}
			for (int j = 0; j < nodes.size(); j+=2) {
				node n = newNode(&nodes[j], &nodes[j + 1], "");
				level.push_back(n);
			}
			nodes = level;
	}
		tree = nodes;
	}
	string getRoot() { return tree[0].hash; }
};