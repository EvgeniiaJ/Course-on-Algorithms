#include <iostream>
#include <fstream>
using namespace std;

void countCharacters(ifstream& input, int* charCounts);
void printArray(int* charCounts, ofstream& output, int size);

void countCharacters(ifstream& input, int* charCounts) {

	char character;

	try {
		if (input.is_open()) {
			while (input.good()) {
				input.get(character);
				charCounts[character]++;
			}
		}
	}
	catch (exception const& e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void printArray(int* charCounts, ofstream& output, int size) {

	try {
		for (int i = 33; i < size; i++) {
			if (charCounts[i] > 0) {
				output << (char)i << " " << charCounts[i] << "\n";
			}
		}
	}
	catch (exception const& e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

int main(int argc, char** argv) {

	ifstream input;
	ofstream output;

	try {

		input.open(argv[1]);
		output.open(argv[2]);

		const int maxCharNumber = 256;
		int charCounts[maxCharNumber];

		for (int i = 0; i < maxCharNumber; i++) {
			charCounts[i] = 0;
		}

		countCharacters(input, charCounts);
		printArray(charCounts, output, maxCharNumber);

		input.close();
		output.close();

	}
	catch (exception const& e) {
		cout << "There is an error: " << e.what() << endl;
	}
	return 0;
}