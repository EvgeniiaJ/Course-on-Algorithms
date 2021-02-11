#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void ExternalFileMergeSort(ifstream& input1, ifstream& input2, ofstream& output) {

	int num1, num2;
	input1 >> num1;
	input2 >> num2;
	
	while (!input1.eof() || !input2.eof()) {
		if (num1 < num2) {
			output << num1 << endl;
			input1 >> num1;
		}
		else {
			output << num2 << endl;
			input2 >> num2;
		}
	}

	while (!input1.eof()) {
		input1 >> num1;
		output << to_string(num1) << endl;
	}

	while (!input2.eof()) {
		output << to_string(num2) << endl;
		input2 >> num2;
	}

	if (num1 < num2) {
		output << to_string(num1) << endl;
		output << to_string(num2) << endl;
	}
	else {
		output << to_string(num2) << endl;
		output << to_string(num1) << endl;
	}
}

int main(int argc, char** argv) {
	ifstream input1;
	ifstream input2;
	ofstream output;
	try {

		input1.open(argv[1]);
		input2.open(argv[2]);
		output.open(argv[3]);

		ExternalFileMergeSort(input1, input2, output);

		input1.close();
		input2.close();
		output.close();
	}
	catch (exception e) {
		cout << "There is an error: " << e.what();
	}
	return 0;
}
