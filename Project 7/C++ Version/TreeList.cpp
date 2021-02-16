#include "TreeList.h"
#include <iostream>


TreeList::TreeList() {
	this->listHead = new TreeNode();
}

TreeList::~TreeList() {

}

TreeNode* TreeList::getListHead() {
	return this->listHead;
}

void TreeList::setListHead(TreeNode* listHead) {
	this->listHead = listHead;
}

void TreeList::insertNewNode(TreeNode* head, TreeNode* newNode) {
	TreeNode* spot = findSpot(head, newNode);
	insert(spot, newNode);
}

TreeNode* TreeList::findSpot(TreeNode* head, TreeNode* newNode) {
	TreeNode* spot = head;
	while (spot->getNext() != NULL && spot->getNext()->getProbability() < newNode->getProbability()) {
		spot = spot->getNext();
	}
	return spot;
}

void TreeList::insert(TreeNode* spot, TreeNode* newNode) {
	newNode->setNext(spot->getNext());
	spot->setNext(newNode);
}

void TreeList::printList(TreeNode* head, ofstream& output) {
	string str = "listHead --> ";
	try {
		for (TreeNode* node = head; node->getNext() != NULL; node = node->getNext()) {
			str += node->printNode();
		}
		str += "NULL\n";
		output << str;
	}
	catch (exception e) {
		cout << e.what();
	}
}