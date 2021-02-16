#pragma once
#include <fstream>
#include "TreeNode.h"
using namespace std;

class TreeList {

private:
	TreeNode* listHead;

public:
	TreeList();

	~TreeList();

	TreeNode* getListHead();

	void setListHead(TreeNode*);

	void insertNewNode(TreeNode*, TreeNode*);

	TreeNode* findSpot(TreeNode*, TreeNode*);

	void insert(TreeNode*, TreeNode*);

	void printList(TreeNode*, ofstream&);

};
