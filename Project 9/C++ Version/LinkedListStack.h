#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "ListNode.h"


class LinkedListStack {
private:
	ListNode* top;
public:
	LinkedListStack();

	~LinkedListStack();

	ListNode* getTop();

	void setTop(ListNode*);

	void push(ListNode*);

	ListNode* pop();

	bool isEmpty();

	void printStack(ListNode*, ofstream&);
};
