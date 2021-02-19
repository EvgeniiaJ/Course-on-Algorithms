#include "Node.h"

Node::Node() {
	this->jobId = 0;
	this->jobTime = 0;
	this->dependentCounter = 0;
	this->next = nullptr;
}

Node::~Node(){
	delete[] next;
}

Node::Node(int jobId, int jobTime, int dependentCount){
	this->jobId = jobId;
	this->jobTime = jobTime;
	this->dependentCounter = dependentCount;
	this->next = nullptr;
}

int Node::getJobId() {
	return jobId;
}

void Node::setJobId(int jobId) {
	this->jobId = jobId;
}

int Node::getJobTime() {
	return jobTime;
}

void Node::setJobTime(int jobTime) {
	this->jobTime = jobTime;
}

int Node::getDependentCounter() {
	return this->dependentCounter;
}

void Node::setDependentCounter(int dependentCounter) {
	this->dependentCounter = dependentCounter;
}

Node* Node::getNext() {
	return next;
}

void Node::setNext(Node* next) {
	this->next = next;
}

void Node::printNode(ofstream& output){
	string str = " --> ";

	try {
		str += ("(" + to_string(this->getJobId()) + "," + to_string(this->getJobTime()) + "," + to_string(this->getDependentCounter()) + ","
			+ to_string(this->getNext()->getJobId()) + ") --> ");

		output << str;
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}

}

