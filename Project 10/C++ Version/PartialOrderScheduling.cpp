#include "PartialOrderScheduling.h"

PartialOrderScheduling::PartialOrderScheduling(){
	this->currentTime = 0;
	this->processorsUsed = 0;
	Node* dummy = new Node();
	open = dummy;
}

void PartialOrderScheduling::initialize(ifstream& input1, ifstream& input2, int processorsNumber){
	if (processorsNumber <= 0) {
		cout << "Should be 1 processor or more" << endl;
		exit(0);
	}
	else {
		this->processorsNumber = processorsNumber;
	}
	if (!input1.eof()) {
		input1 >> this->nodesNumber;
	}
	if (processorsNumber > nodesNumber) {
		processorsNumber = nodesNumber;
	}

	jobsArray = new Job[nodesNumber + 1];
	processorsArray = new Processor[processorsNumber + 1];
	adjacencyMatrix = new int*[nodesNumber + 1];
	parentCountArray = new int[nodesNumber + 1];
	dependentCountArray = new int[nodesNumber + 1];
	onGraphArray = new int[nodesNumber + 1];

	for (int i = 0; i <= nodesNumber; i++) {
		Job* job = new Job();
		jobsArray[i] = *job;
		parentCountArray[i] = 0;
		dependentCountArray[i] = 0;
		onGraphArray[i] = 0;
		adjacencyMatrix[i] = new int[nodesNumber + 1];
		for (int j = 0; j <= nodesNumber; j++) {
			adjacencyMatrix[i][j] = 0;
		}
	}

	loadMatrix(input1);
	
	computeParentCount(adjacencyMatrix, parentCountArray);
	computeDependentCount(adjacencyMatrix, dependentCountArray);
	totalJobTimes = constructJobArray(input2, adjacencyMatrix);
	
	scheduleTable = new int*[processorsNumber + 1];
	for (int i = 0; i <= processorsNumber; i++) {
		Processor* processor = new Processor(0, 0);
		processorsArray[i] = *processor;
		scheduleTable[i] = new int[totalJobTimes + 1];
		for (int j = 0; j <= totalJobTimes; j++) {
			scheduleTable[i][j] = 0;
		}
	}

}

void PartialOrderScheduling::loadMatrix(ifstream& input){
	int i, j;
	while (!input.eof()) {
		input >> i >> j;
		this->adjacencyMatrix[i][j] = 1;
		this->onGraphArray[i] = 1;
		this->onGraphArray[j] = 1;
	}
}

void PartialOrderScheduling::loadOpen(){
	int orphanNode = findOrphan();
	while (orphanNode > 0) {
		if (orphanNode > 0) {
			int jobId = orphanNode;
			int jobTime = jobsArray[jobId].getJobTime();
			Node* newNode = new Node(jobId, jobTime, jobsArray[jobId].getDependentCounter());
			openInsert(newNode);
		}
		orphanNode = findOrphan();
	}
}

void PartialOrderScheduling::loadProcessorArray(int){
	int availProc = findProcessor();
	while (availProc > 0 && open->getNext() != nullptr && processorsUsed < processorsNumber) {
		if (availProc > 0) {
			processorsUsed++;
			Node* newJob = removeFront();
			int jobId = newJob->getJobId();
			int jobTime = newJob->getJobTime();
			processorsArray[availProc].setDoWhichJob(jobId);
			processorsArray[availProc].setTimeRemain(jobTime);
			putJobOnTable(availProc, currentTime, jobId, jobTime);
			//				availProc = findProcessor();
		}
		availProc = findProcessor();
	}
}

int PartialOrderScheduling::findOrphan(){
	for (int i = 1; i <= nodesNumber; i++) {
		if (jobsArray[i].getParentCounter() <= 0 && jobsArray[i].getOnOpen() == 0 && jobsArray[i].getOnWhichProcessor() <= 0) {
			jobsArray[i].setOnOpen(1);
			return i;
		}
	}
	return -1;
}

void PartialOrderScheduling::openInsert(Node* newNode){
	Node* spot = findSpot(newNode);
	newNode->setNext(spot->getNext());
	spot->setNext(newNode);
}

Node* PartialOrderScheduling::findSpot(Node* newNode){
	Node* spot = open;
	while (spot->getNext() != nullptr && spot->getNext()->getDependentCounter() >= newNode->getDependentCounter()) {
		spot = spot->getNext();
	}
	return spot;
}

int PartialOrderScheduling::constructJobArray(ifstream& input, int** matrix){
	int totalTime = 0;
	int nodeId = 0, jobTime= 0;
	int skip = 0;
	if (!input.eof()) {
		input >> skip;
	}
	while (!input.eof()) {
		input >> nodeId;
		input >> jobTime;
		totalTime += jobTime;
		jobsArray[nodeId].setJobTime(jobTime);
		jobsArray[nodeId].setOnWhichProcessor(-1);
		jobsArray[nodeId].setOnOpen(0);
		jobsArray[nodeId].setParentCounter(parentCountArray[nodeId]);
		jobsArray[nodeId].setDependentCounter(dependentCountArray[nodeId]);
	
	}
	return totalTime;
}

void PartialOrderScheduling::computeParentCount(int** matrix, int* countArray){
	for (int nodeId = 1; nodeId <= nodesNumber; nodeId++) {
		int sum = 0;
		for (int i = 1; i <= nodesNumber; i++) {
			sum += matrix[i][nodeId];
		}
		countArray[nodeId] = sum;
	}
}

void PartialOrderScheduling::computeDependentCount(int** matrix, int* countArray){
	for (int nodeId = 1; nodeId <= nodesNumber; nodeId++) {
		int sum = 0;
		for (int i = 1; i <= nodesNumber; i++) {
			sum += matrix[nodeId][i];
		}
		countArray[nodeId] = sum;
	}
}

Node* PartialOrderScheduling::removeFront(){
	Node* newNode = open->getNext();
	open->setNext(open->getNext()->getNext());
	newNode->setNext(nullptr);
	return newNode;
}

void PartialOrderScheduling::printList(ofstream& output){
	string str = "OPEN --> ";
	string out = "OPEN-->";

	try {
		for (Node* i = open; i->getNext() != nullptr; i = i->getNext()) {
			if (i->getNext() == nullptr) {
				str = "NULL) --> ";
			}
			else {
				str = "\"" + to_string(i->getNext()->getJobTime()) + "\") --> ";
			}
			out += "(\"" + to_string(i->getJobId()) + "\", " + to_string(i->getJobTime()) + ", " + str;
		}
		out += "NULL\n";
		output << out;

		
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void PartialOrderScheduling::printScheduleTable(ofstream& output){
	try {
		output << "     -0--";
		for (int i = 1; i < totalJobTimes + 1; i++) {
			output << "-" + to_string(i) + "--";
		}
		output << endl;
		for (int i = 1; i < processorsNumber + 1; i++) {
			output << "P(" + to_string(i) + ")|";
			for (int j = 0; j < totalJobTimes + 1; j++) {
				if (scheduleTable[i][j] == 0) {
					output << " - |";
				}
				else {
					output << " " << scheduleTable[i][j] << " |";
				}
			}
			output << " \n";
			output << "     -";
			for (int k = 0; k <= totalJobTimes * 4; k++) {
				output << "-";
			}
			output << endl;
		}
		output << "\n";
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

int PartialOrderScheduling::findProcessor(){
	for (int i = 1; i <= processorsNumber; i++) {
		if (processorsArray[i].getTimeRemain() <= 0) {
			return i;
		}
	}
	return -1;
}

void PartialOrderScheduling::putJobOnTable(int availableProcessor, int currentTime, int jobId, int jobTime){
	int time = currentTime;
	int endTime = time + jobTime;
	while (time < endTime) {
		scheduleTable[availableProcessor][time] = jobId;
		time++;
	}
}

bool PartialOrderScheduling::checkCycle(){
	if (open->getNext() == nullptr && !graphIsEmpty() && jobsFinished()) {
		return true;
	}
	return false;
}

bool PartialOrderScheduling::graphIsEmpty(){
	for (int i = 1; i <= nodesNumber; i++) {
		if (onGraphArray[i] > 0) {
			return false;
		}
	}
	return true;
}

bool PartialOrderScheduling::jobsFinished(){
	for (int i = 1; i <= processorsNumber; i++) {
		if (processorsArray[i].getTimeRemain() > 0 && processorsArray[i].getDoWhichJob() > 0) {
			return false;
		}
	}
	return true;
}

void PartialOrderScheduling::updateProcessorTime(){
	for (int i = 1; i <= processorsNumber; i++) {
		if (processorsArray[i].getTimeRemain() > 0) {
			processorsArray[i].setTimeRemain(processorsArray[i].getTimeRemain() - 1);
		}
	}
}

int PartialOrderScheduling::findDoneProcessor(){
	for (int i = 1; i <= processorsNumber; i++) {
		if (processorsArray[i].getTimeRemain() <= 0 && processorsArray[i].getDoWhichJob() > 0) {
			int jobId = processorsArray[i].getDoWhichJob();
			processorsArray[i].setDoWhichJob(-1);
			processorsUsed--;
			return jobId;
		}
	}
	return -1;
}

void PartialOrderScheduling::deleteEdge(int jobId){
	for (int dependent = 1; dependent <= nodesNumber; dependent++) {
		if (adjacencyMatrix[jobId][dependent] > 0) {
			parentCountArray[dependent]--;
			adjacencyMatrix[jobId][dependent] = 0;
			int parentCounter = (jobsArray[dependent].getParentCounter()) - 1;
			jobsArray[dependent].setParentCounter(parentCounter);
		}
	}
}
