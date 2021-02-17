#pragma once
#include <iostream>
using namespace std;

class ListNode{

private:
	int data;
	ListNode* next;
public:
	ListNode();

	ListNode(int);

	int getData();

	void setData(int);

	ListNode* getNext();

	void setNext(ListNode*);

};

