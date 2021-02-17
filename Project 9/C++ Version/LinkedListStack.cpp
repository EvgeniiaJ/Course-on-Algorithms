#include "LinkedListStack.h"

LinkedListStack::LinkedListStack() {
	this->top = NULL;
}

LinkedListStack::~LinkedListStack(){
}

ListNode* LinkedListStack::getTop() {
	return top;
}

void LinkedListStack::setTop(ListNode* top) {
	this->top = top;
}

void LinkedListStack::push(ListNode* newNode) {
	newNode->setNext(top);
	top = newNode;
}

ListNode* LinkedListStack::pop() {
	if (top == NULL) {
		return NULL;
	}
	else {
		ListNode* remove = top;
		top = top->getNext();
		remove->setNext(NULL);
		return remove;
	}
}

bool LinkedListStack::isEmpty() {
	return (top == NULL);
}

void LinkedListStack::printStack(ListNode* top, ofstream& output) {
	string str = "Top --> ";
	ListNode* node = top;
	try {
		for (node = top; node->getNext() != NULL; node = node->getNext()) {
			str.append("(" + to_string(node->getData()));
			str.append(", " + to_string(node->getNext()->getData()));
			str.append(") --> ");
		}
		str.append("(" + to_string(node->getData()));
		str.append(", NULL) --> NULL\n\n");
		output << str;
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}