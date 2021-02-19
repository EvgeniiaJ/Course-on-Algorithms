#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node{

private:
	int jobId;
	int jobTime;
	int dependentCounter;
	Node* next;

public:
	Node();

	~Node();

	Node(int, int, int);
	
	int getJobId();

	void setJobId(int);

	int getJobTime();

	void setJobTime(int);

	int getDependentCounter();

	void setDependentCounter(int);

	Node* getNext();

	void setNext(Node*);

	void printNode(ofstream& output);
};
