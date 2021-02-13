#include <iostream>
#include <fstream>
#include <string>

#include "RunLengthEncoding.h"

using namespace std;

int main(int argc, char** argv) {

	ifstream input;
	ofstream encode;
	ofstream decoding;

	try {
		int whichMethod = 1;
		string inputFileString = argv[1];
		string encodedFileString = inputFileString.substr(0, inputFileString.find_last_of('.')) + "_EncodeMethod" + to_string(whichMethod) + ".txt";
		string decodedFileString = encodedFileString.substr(0, encodedFileString.find_last_of('.')) + "_Decoded.txt";
		
		input.open(inputFileString);
		encode.open(encodedFileString);
		decoding.open(decodedFileString);

		RunLengthEncoding* encoding = new RunLengthEncoding(input);
		encoding->encodeMethod1(input, encode);
		ifstream newInput;
		newInput.open(encodedFileString);
		encoding->decodMethod1(newInput, decoding);
		newInput.close();
		decoding.close();
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
	return 0;
}