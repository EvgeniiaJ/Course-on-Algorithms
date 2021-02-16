#pragma once
#include <iostream>
#include <fstream>

#include "TreeNode.h"
#include "TreeList.h"

class HuffmanBinaryTree {

private:
	TreeNode* root;

public:
	TreeList* list;
	string charCodes[256];	

public:

	HuffmanBinaryTree();

	~HuffmanBinaryTree();

	TreeNode* getRoot();

	void setRoot(TreeNode*);

	void constructHuffmanLinkedList(int* , ofstream&);

	void constructHuffmanBinaryTree(TreeList* , ofstream&);

	bool isLeaf(TreeNode*);

	void constructCodes(TreeNode*, string);

	void preOrderTraversal(TreeNode*, ofstream&);

	void inOrderTraversal(TreeNode*, ofstream&);

	void postOrderTraversal(TreeNode*, ofstream&);

};