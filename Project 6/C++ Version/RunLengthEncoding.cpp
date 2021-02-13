#include "RunLengthEncoding.h"
#include <iostream>
//using namespace std;


RunLengthEncoding::RunLengthEncoding(ifstream &input) {
	input >> this->numRows;
	input >> this->numCols;
	input >> this->minVal;
	input >> this->maxVal;
	this->whichMethod = 1;
	
	decodedArray = new int* [numRows];
	for (int i = 0; i < numRows; i++) {
		decodedArray[i] = new int[numCols];
		for (int j = 0; j < numCols; j++) {
			decodedArray[i][j] = 0;
		}
	}
}

void RunLengthEncoding::encodeMethod1(ifstream& input, ofstream& output) {
	int row = 0;
	int col = 0;
	int length = 0;
	int currentVal = -1;
	int nextVal = -1;

	try {
		output << numRows << " " << numCols << " " << minVal << " " << maxVal << " " << endl << this->whichMethod << endl;
		while (row < numRows) {
			col = 0;
			length = 0;
			input >> currentVal;
			output << row << " " << col << " " << currentVal << " ";
			length++;

			while (col < numCols - 1) {
				col++;
				input >> nextVal;

				if (nextVal == currentVal) {
					length++;
				}
				else {
					output << length << endl;
					currentVal = nextVal;
					length = 1;
					output << row << " " << col << " " << currentVal << " ";
				}
			}
			output << length << endl;
			row++;
		}
		input.close();
		output.close();
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void RunLengthEncoding::decodMethod1(ifstream& input, ofstream& output) {
	int row;
	int col;
	int value;
	int length;

	try {
		input >> numRows >> numCols >> minVal >> maxVal >> whichMethod;
		output << numRows << " " << numCols << " " << minVal << " " << maxVal << " " << endl;

		while (!input.eof()) {
			input >> row >> col >> value >> length;
			while (length > 0) {
				this->decodedArray[row][col] = value;
				col++;
				length--;
			}
		}

		printDecodedImage(this->decodedArray, output);
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void RunLengthEncoding::printDecodedImage(int** array, ofstream& output) {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			output << array[i][j] << " ";
		}
		output << endl;
	}
}
