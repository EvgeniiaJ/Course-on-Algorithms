#include <iostream>
#include <fstream>
#include <string>

#include "PartialOrderScheduling.h"

using namespace std;

int main(int argc, char** argv) {

	string inputFileName1 = argv[1]; // graph input
	string inputFileName2 = argv[2]; // jobTime input
	string outputFileName1 = argv[3]; // output file 1
	string outputFileName2 = argv[4]; // output file 2
	string numOfProcs = argv[5]; // number of processors
	bool hasCycle = false;

	ifstream input1;
	ifstream input2;
	ofstream output1;
	ofstream output2;
	
	try {
		input1.open(inputFileName1);
		input2.open(inputFileName2);
		output1.open(outputFileName1);
		output2.open(outputFileName2);

		PartialOrderScheduling* schedule = new PartialOrderScheduling();

		schedule->initialize(input1, input2, stoi(numOfProcs));
		schedule->currentTime = 0;
		while (!schedule->graphIsEmpty()) {
			schedule->loadOpen();
			schedule->printList(output2);
			schedule->loadProcessorArray(schedule->currentTime);
			hasCycle = schedule->checkCycle();
			if (hasCycle) {
				cout << "There is a cycle in the graph!" << endl;
				output1 << "There is a cycle in the graph!" << endl;
				exit(0);
			}
			schedule->printScheduleTable(output1);
			schedule->currentTime++;
			schedule->updateProcessorTime();
			int jobId = schedule->findDoneProcessor();
			while (jobId > 0) {
				
				if (jobId > 0) {
					schedule->onGraphArray[jobId] = 0;
					schedule->deleteEdge(jobId);
				}
				jobId = schedule->findDoneProcessor();
			}
		}
		schedule->printScheduleTable(output1);
		
		input1.close();
		input2.close();
		output1.close();
		output2.close();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	return 0;
}

