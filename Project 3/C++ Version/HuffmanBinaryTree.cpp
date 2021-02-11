#include "HuffmanBinaryTree.h"


HuffmanBinaryTree::HuffmanBinaryTree() {
	this->root = new TreeNode();
	this->list = new TreeList();
}

HuffmanBinaryTree::~HuffmanBinaryTree() {}

TreeNode* HuffmanBinaryTree::getRoot() {
	return this->root;
}

void HuffmanBinaryTree::setRoot(TreeNode* root) {
	this->root = root;
}

void HuffmanBinaryTree::constructHuffmanLinkedList(TreeList* list, ifstream& input, ofstream& output) {
	this->list = list;

	string characterString = "";
	int probability = 0;

	try {
		while (!input.eof()) {
			input >> characterString >> probability;			
			TreeNode* newNode = new TreeNode(characterString, probability, "", NULL, NULL, NULL);
			list->insertNewNode(list->getListHead(), newNode);
			list->printList(list->getListHead(), output);			
		}
		input.close();
		output << "\n\n";
	}
	catch (exception e) {
		cout << e.what();
	}
	
}

void HuffmanBinaryTree::constructHuffmanBinaryTree(TreeList* list, ofstream& output) {
	TreeNode* spot = this->list->getListHead()->getNext();
	list->printList(list->getListHead(), output);
	while (spot->getNext() != NULL) {
		string newCharacterString = spot->getCharString() + spot->getNext()->getCharString();
		int newProbability = spot->getProbability() + spot->getNext()->getProbability();
		TreeNode* newLeft = spot;
		TreeNode* newRight = spot->getNext();
		TreeNode* newNode = new TreeNode(newCharacterString, newProbability, "", newLeft, newRight, NULL);
		list->insertNewNode(list->getListHead(), newNode);
		list->printList(list->getListHead(), output);
		spot = spot->getNext()->getNext();
		this->setRoot(newNode);
	}
}

bool HuffmanBinaryTree::isLeaf(TreeNode* node) {
	return (!(node->hasLeft()) && !(node->hasRight()));
}

void HuffmanBinaryTree::constructCodes(TreeNode* node, string code, ofstream& output) {
	try {
		if (isLeaf(node)) {
			node->setCode(code);
			output << node->getCharString() + " " + node->getCode() << endl;
		}
		else {
			constructCodes(node->getLeft(), code + "0", output);
			constructCodes(node->getRight(), code + "1", output);
		}
	}
	catch (exception e) {
		cout << e.what();
	}
}

void HuffmanBinaryTree::preOrderTraversal(TreeNode* node, ofstream& output) {
	try {
		if (isLeaf(node)) {
			output << node->printNode() << "\n";
		}
		else {
			output << node->printNode() << "\n";
			preOrderTraversal(node->getLeft(), output);
			preOrderTraversal(node->getRight(), output);
		}
	}
	catch (exception e) {
		cout << e.what();
	}
}

void HuffmanBinaryTree::inOrderTraversal(TreeNode* node, ofstream& output) {
	try {
		if (isLeaf(node)) {
			output << node->printNode() << "\n";
		}
		else {
			inOrderTraversal(node->getLeft(), output);
			output << node->printNode() << "\n";			
			inOrderTraversal(node->getRight(), output);
		}
	}
	catch (exception e) {
		cout << e.what();
	}
}

void HuffmanBinaryTree::postOrderTraversal(TreeNode* node, ofstream& output) {
	try {
		if (isLeaf(node)) {
			output << node->printNode() << "\n";
		}
		else {
			postOrderTraversal(node->getLeft(), output);
			postOrderTraversal(node->getRight(), output);
			output << node->printNode() << "\n";			
		}
	}
	catch (exception e) {
		cout << e.what();
	}
}