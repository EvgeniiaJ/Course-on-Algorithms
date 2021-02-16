#include "HuffmanBinaryTree.h"


HuffmanBinaryTree::HuffmanBinaryTree() {
	this->root = new TreeNode();
	this->list = new TreeList();
	for (int i = 0; i < 256; i++) {
		charCodes[i] = "";
	}

}

HuffmanBinaryTree::~HuffmanBinaryTree() {}

TreeNode* HuffmanBinaryTree::getRoot() {
	return this->root;
}

void HuffmanBinaryTree::setRoot(TreeNode* root) {
	this->root = root;
}

void HuffmanBinaryTree::constructHuffmanLinkedList(int* countArray, ofstream& output) {

	char character;
	int probability = 0;

	try {
		output << "\nConstructing Huffman Linked List:\n";
		for (int i = 0; i < 256; i++) {
			if (countArray[i] > 0) {
				character = (char)i;
				probability = countArray[i];
				TreeNode* newNode = new TreeNode(character, probability);
				list->insertNewNode(list->getListHead(), newNode);
			}
		}
		list->printList(list->getListHead(), output);
	}
	catch (exception e) {
		cout << e.what();
	}

}

void HuffmanBinaryTree::constructHuffmanBinaryTree(TreeList* list, ofstream& output) {
	TreeNode* spot = this->list->getListHead()->getNext();
	try {
		output << "\nConstructing Huffman Binary Tree:\n";
		while (spot->getNext() != NULL) {
			string newCharacterString = spot->getCharString() + spot->getNext()->getCharString();
			int newProbability = spot->getProbability() + spot->getNext()->getProbability();
			TreeNode* newLeft = spot;
			TreeNode* newRight = spot->getNext();
			TreeNode* newNode = new TreeNode(newCharacterString, newProbability, "", newLeft, newRight, NULL);
			list->insertNewNode(spot, newNode);
			spot = spot->getNext()->getNext();
			this->setRoot(newNode);
		}
		list->printList(list->getListHead(), output);
	}
	catch (exception e) {
		cout << e.what();
	}
}

bool HuffmanBinaryTree::isLeaf(TreeNode* node) {
	return (!(node->hasLeft()) && !(node->hasRight()));
}

void HuffmanBinaryTree::constructCodes(TreeNode* node, string code) {
	int index = 0;
	try {
		if (isLeaf(node)) {
			node->setCode(code);
			index = (int)node->getCharacter();
			if (node->getCode() != "") {
				charCodes[index] = node->getCode();
			}
		}
		else {
			constructCodes(node->getLeft(), code + "0");
			constructCodes(node->getRight(), code + "1");
		}
	}
	catch (exception e) {
		cout << e.what();
	}
}

void HuffmanBinaryTree::preOrderTraversal(TreeNode* node, ofstream& output) {
	try {
		if (isLeaf(node)) {
			output << node->printNode();
		}
		else {
			output << node->printNode();
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
			output << node->printNode();
		}
		else {
			inOrderTraversal(node->getLeft(), output);
			output << node->printNode();
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
			output << node->printNode();
		}
		else {
			postOrderTraversal(node->getLeft(), output);
			postOrderTraversal(node->getRight(), output);
			output << node->printNode();
		}
	}
	catch (exception e) {
		cout << e.what();
	}
}