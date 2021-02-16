#pragma once
#include <string>
using namespace std;

class TreeNode {

private:
	string charString;
	char character;
	int probability;
	string code;
	TreeNode* left;
	TreeNode* right;
	TreeNode* next;

public:
	TreeNode();

	TreeNode(string, int, string, TreeNode*, TreeNode*, TreeNode*);

	TreeNode(char, int);

	~TreeNode();

	string getCharString();

	void setCharString(string);

	char getCharacter();

	void setCharacter(char);

	int getProbability();

	void setProbability(int);

	string getCode();

	void setCode(string);

	TreeNode* getLeft();

	void setLeft(TreeNode*);

	TreeNode* getRight();

	void setRight(TreeNode*);

	TreeNode* getNext();

	void setNext(TreeNode*);

	bool hasNext();

	bool hasLeft();

	bool hasRight();

	string printNode();
};
