#include "BucketSort.h"

BucketSort::BucketSort(ifstream& input) {
	try {
		int data;
		input >> this->max;

		while (!input.eof()) {
			input >> data;
			if (data > max) {
				max = data;
			}
		}
		initArray();
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void BucketSort::initArray() {
	this->BucketArray = new int[this->max + 1];
	for (int i = 0; i <= max; i++) {
		BucketArray[i] = 0;
	}
}
void BucketSort::fillOutBuckets(ifstream& input, ofstream& output) {
	int data;
	try {
		while (!input.eof()) {
			input >> data;
			BucketArray[data]++;
			for (int i = 0; i <= max; i++) {
				output << "bucket #" << i << " " << BucketArray[i] << endl;
			}
			output << endl;
		}

		output << "\n\n The Final Result of Sorted Array:\n";
		for (int i = 0; i <= max; i++) {
			if (BucketArray[i] > 0) {
				output << i << " " << BucketArray[i] << endl;
			}
		}
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void BucketSort::printResult(ofstream& output) {
	int index = 0;
	try {
		output << "Displaying Sorted Numbers:" << endl;
		while (index <= max) {
			while (BucketArray[index] > 0){
			output << index << " ";
			BucketArray[index]--;
			}
			index++;
		}
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}