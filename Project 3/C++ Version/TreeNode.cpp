#include "TreeNode.h"

TreeNode::TreeNode() {

	this->charString = "dummy";
	this->probability = 0;
	this->code = "";
	this->left = NULL;
	this->right = NULL;
	this->next = NULL;
}

TreeNode::TreeNode(string charString, int probability, string code, TreeNode* left, TreeNode* right, TreeNode* next) {
	this->charString = charString;
	this->probability = probability;
	this->code = code;
	this->left = left;
	this->right = right;
	this->next = next;
}

TreeNode::~TreeNode() {
}

string TreeNode::getCharString() {
	return this->charString;
}

void TreeNode::setCharString(string charString) {
	this->charString = charString;
}

int TreeNode::getProbability() {
	return this->probability;
}

void TreeNode::setProbability(int probability) {
	this->probability = probability;
}

string TreeNode::getCode() {
	return this->code;
}

void TreeNode::setCode(string code) {
	this->code = code;
}

TreeNode* TreeNode::getLeft() {
	return this->left;
}

void TreeNode::setLeft(TreeNode* left) {
	this->left = left;
}

TreeNode* TreeNode::getRight() {
	return this->right;
}

void TreeNode::setRight(TreeNode* right) {
	this->right = right;
}

TreeNode* TreeNode::getNext() {
	return this->next;
}

void TreeNode::setNext(TreeNode* next) {
	this->next = next;
}

bool TreeNode::hasNext() {
	return (this->getNext() != NULL);
}

bool TreeNode::hasLeft() {
	return (this->getLeft() != NULL);
}

bool TreeNode::hasRight() {
	return (this->getRight() != NULL);
}

string TreeNode::printNode() {
	string str = "(\"" + this->getCharString() + "\", " + to_string(this->getProbability()) + ", \"";
	if (this->hasNext()) {
		str += this->getNext()->getCharString() + "\", ";
	}
	else {
		str += "NULL, ";
	}
	if (this->hasLeft()) {
		str += this->getLeft()->getCharString() + "\", ";
	}
	else {
		str += "NULL, ";
	}
	if (this->hasRight()) {
		str += this->getRight()->getCharString() + "\")";
	}
	else {
		str += "NULL)";
	}
	return str;
}