#include <iostream>
#include <fstream>
#include <string>

#include "ListNode.h"
#include "LinkedListStack.h"
#include "LinkedListQueue.h"
#include "RadixSort.h"

using namespace std;

int main(int argc, char** argv) {

	string inputFileName = argv[1];
	string output1FileName = argv[2];
	string output2FileName = argv[3];

	try {

		ifstream input;
		ofstream output1;
		ofstream output2;

		input.open(inputFileName);
		output1.open(output1FileName);
		output2.open(output2FileName);


		RadixSort* sorting = new RadixSort(input);
		input.close();

		ifstream input1;
		input1.open(inputFileName);

		sorting->loadStack(input1, output2);

		sorting->Sorting(output1, output2);

		input1.close();
		output1.close();
		output2.close();

	}
	catch (exception e) {
		cout << "There is an error: " << e.what();
	}
	return 0;
}