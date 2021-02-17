#pragma once
#include <string>

#include "ListNode.h"

class LinkedListQueue{

private:
	ListNode* head;
	ListNode* tail;

public:
	ListNode* dummy;

	LinkedListQueue();

	ListNode* getHead();

	void setHead(ListNode*);

	ListNode* getTail();

	void setTail(ListNode*);

	bool isEmpty(LinkedListQueue);

	bool isEmpty(LinkedListQueue*);

	void addTail(LinkedListQueue*, ListNode*);

	ListNode* deleteHead(LinkedListQueue*);

	string printQueue(int);
};

