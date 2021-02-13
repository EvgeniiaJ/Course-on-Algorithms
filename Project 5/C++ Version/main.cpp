#include <iostream>
#include <fstream>
#include "BucketSort.h"

using namespace std;

int main(int argc, char** argv) {

	ifstream input;
	ofstream debug;
	ofstream result;
	try {
		input.open(argv[1]);
		debug.open(argv[2]);
		result.open(argv[3]);

		BucketSort* sorting = new BucketSort(input);
		input.close();

		input.open(argv[1]);
		sorting->fillOutBuckets(input, debug);
		sorting->printResult(result);

		input.close();
		debug.close();
		result.close();
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
	return 0;
}