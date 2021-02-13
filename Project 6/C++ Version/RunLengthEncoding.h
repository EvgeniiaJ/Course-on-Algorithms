#pragma once
#include <fstream>
using namespace std;

class RunLengthEncoding {
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int whichMethod;
	int** decodedArray;

	RunLengthEncoding(ifstream&);

	void encodeMethod1(ifstream&, ofstream&);

	void decodMethod1(ifstream&, ofstream&);

	void printDecodedImage(int**, ofstream&);
};