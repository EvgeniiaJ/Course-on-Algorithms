#pragma once
#include <fstream>
#include <string>

#include "ListNode.h"
#include "LinkedListStack.h"
#include "LinkedListQueue.h"
using namespace std;

class RadixSort{
public:
	int tableSize;
	int data;
	int currentTable;
	int previousTable;
	int maxDigit;
	int offset;
	int currentDigit;
	int currentQueue;
	LinkedListStack* stack;
	LinkedListQueue** hashTable;

	RadixSort(ifstream&);

	void init();

	int getMaxDigit(int);

	void loadStack(ifstream&, ofstream&);

	void dumpStack(ListNode*, int, int, ofstream&);

	int getDigit(ListNode*, int);

	void printTable(LinkedListQueue*, ofstream&);

	void printSortResult(LinkedListQueue*, ofstream&);

	void subtractOffset();

	void Sorting(ofstream&, ofstream&);
};

