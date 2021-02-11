#pragma once
#include "TreeNode.h"
#include "TreeList.h"
#include <iostream>
#include <fstream>

class HuffmanBinaryTree {

private:
	TreeNode* root;
	TreeList* list;

public:

	HuffmanBinaryTree();

	~HuffmanBinaryTree();

	TreeNode* getRoot();

	void setRoot(TreeNode*);

	void constructHuffmanLinkedList(TreeList*, ifstream&, ofstream&);

	void constructHuffmanBinaryTree(TreeList* list, ofstream&);
	
	bool isLeaf(TreeNode*);

	void constructCodes(TreeNode*, string, ofstream&);

	void preOrderTraversal(TreeNode*, ofstream&);

	void inOrderTraversal(TreeNode*, ofstream&);

	void postOrderTraversal(TreeNode*, ofstream&);


};
