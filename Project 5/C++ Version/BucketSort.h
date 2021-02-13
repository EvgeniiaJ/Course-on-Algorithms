#include <iostream>
#include <fstream>
using namespace std;

class BucketSort {
public:
	int max;
	int* BucketArray;

	BucketSort(ifstream&);
	
	void initArray();

	void fillOutBuckets(ifstream&, ofstream&);

	void printResult(ofstream&);
};
