#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "Node.h"
#include "Job.h"
#include "Processor.h"

using namespace std;

class PartialOrderScheduling{

public:
	int nodesNumber;
	int processorsNumber;
	int processorsUsed;
	Job* jobsArray;
	Processor* processorsArray;
	Node* open;
	int** adjacencyMatrix;
	int* parentCountArray;
	int* dependentCountArray;
	int* onGraphArray;
	int totalJobTimes;
	int** scheduleTable;
	int currentTime;

	PartialOrderScheduling();

	void initialize(ifstream&, ifstream&, int);

	void loadMatrix(ifstream&);

	void loadOpen();

	void loadProcessorArray(int);

	int findOrphan();

	void openInsert(Node*);

	Node* findSpot(Node*);

	int constructJobArray(ifstream&, int**);

	void computeParentCount(int**, int*);

	void computeDependentCount(int**, int*);

	Node* removeFront();

	void printList(ofstream& output);

	void printScheduleTable(ofstream& output);

	int findProcessor();

	void putJobOnTable(int, int, int, int);

	bool checkCycle();

	bool graphIsEmpty();

	bool jobsFinished();

	void updateProcessorTime();
	
	int findDoneProcessor();

	void deleteEdge(int);
};

