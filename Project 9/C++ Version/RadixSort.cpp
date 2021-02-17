#include "RadixSort.h"

RadixSort::RadixSort(ifstream& input) {
	int minNumber = 0;
	int maxNumber = 0;

	while (!input.eof()) {
		input >> this->data;
		if (data < minNumber) {
			minNumber = data;
		}
		if (data > maxNumber) {
			maxNumber = data;
		}
	}
	offset = abs(minNumber);
	maxNumber += offset;
	maxDigit = getMaxDigit(maxNumber);
	tableSize = 10;
	
	init();
}

void RadixSort::init() {
	hashTable = new LinkedListQueue*[2];
	for (int i = 0; i < 2; i++) {
		hashTable[i] = new LinkedListQueue[tableSize];
		for (int j = 0; j < tableSize; j++) {
			hashTable[i][j] = LinkedListQueue();
		}
	}
}

int RadixSort::getMaxDigit(int maximum) {
	int max = maximum;
	int counter = 0;
	while (max > 0) {
		max /= 10;
		counter++;
	}
	return counter;
}

void RadixSort::loadStack(ifstream& input, ofstream& output) {
	this->stack = new LinkedListStack();
	while (!input.eof()) {
		input >> data;
		data += offset;
		ListNode* newNode = new ListNode(data);
		stack->push(newNode);
	}
	stack->printStack(stack->getTop(), output);
}

void RadixSort::dumpStack(ListNode* top, int currentDigit, int currentTable, ofstream& output) {
	ListNode* node;
	int digit, hashIndex;
	while (!stack->isEmpty()) {
		node = stack->pop();
		digit = getDigit(node, currentDigit);
		hashIndex = digit;
		hashTable[currentTable][hashIndex].addTail(&hashTable[currentTable][hashIndex], node);
	}
	printTable(hashTable[currentTable], output);
}

int RadixSort::getDigit(ListNode* node, int currentDigit) {
	int digit = node->getData();
	while (currentDigit > 0) {
		digit /= 10;
		currentDigit--;
	}
	digit %= 10;
	return digit;
}

void RadixSort::printTable(LinkedListQueue* table, ofstream& output) {
	try {
		int index = 0;
		string str = "";
		while (index < tableSize) {
			LinkedListQueue q = table[index];
			if (!(table[index].isEmpty(table[index]))) {
				str += table[index].printQueue(index);
			}
			index++;
		}
		str += "\n";
		output << str;

	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void RadixSort::printSortResult(LinkedListQueue* hashTable, ofstream& output) {
	int index = 0;
	ListNode* spot = hashTable[index].getHead();
	cout << to_string((hashTable[index].getHead())->getData()) << endl;
	string str = "";
	try {
		output << "Sorted Data:" << endl;
		while (index < tableSize) {
			
			while (spot != NULL) {
				if (spot != NULL) {
					data = spot->getData();
					str.append(to_string(data) +  " ");
					spot = spot->getNext();
				}
			}
			index++;
		}
		output << str;
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void RadixSort::subtractOffset() {
	currentTable = previousTable;
	ListNode* node = hashTable[currentTable][0].getHead();
	while (node != NULL) {
		int newData = node->getData() - offset;
		node->setData(newData);
		node = node->getNext();
	}
}

void RadixSort::Sorting(ofstream& output1, ofstream& output2) {
	ListNode* node;
	int digit, hashIndex, temp;
	currentDigit = 0;
	currentTable = 0;
	dumpStack(stack->getTop(), currentDigit, currentTable, output2);
	currentDigit++;
	currentTable = 1;
	previousTable = 0;
	currentQueue = 0;

	while (currentDigit <= maxDigit) {
		while (currentQueue < tableSize) {
			while (!(hashTable[previousTable][currentQueue].isEmpty(&hashTable[previousTable][currentQueue]))) {
				node = hashTable[previousTable][currentQueue].deleteHead(&hashTable[previousTable][currentQueue]);
				digit = getDigit(node, currentDigit);
				hashIndex = digit;
				hashTable[currentTable][hashIndex].addTail(&hashTable[currentTable][hashIndex], node);
			}
			currentQueue++;
		}
		printTable(hashTable[currentTable], output2);

		temp = currentTable;
		currentTable = previousTable;
		previousTable = temp;
		currentQueue = 0;
		currentDigit++;
	}
	subtractOffset();
	printSortResult(hashTable[currentTable], output1);
}

