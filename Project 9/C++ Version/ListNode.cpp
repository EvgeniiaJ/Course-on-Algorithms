#include "ListNode.h"

ListNode::ListNode() {
	this->data = 0;
	this->next = NULL;
}

ListNode::ListNode(int data) {
	this->data = data;
	this->next = NULL;
}

int ListNode::getData() {
	return data;
}

void ListNode::setData(int data) {
	this->data = data;
}

ListNode* ListNode::getNext() {
	return next;
}

void ListNode::setNext(ListNode* next) {
	this->next = next;
}
