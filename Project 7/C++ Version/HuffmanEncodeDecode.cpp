#include "HuffmanEncodeDecode.h"

HuffmanEncodeDecode::HuffmanEncodeDecode() {
	charCountsArray = new int[256];
	for (int i = 0; i < 256; i++) {
		charCountsArray[i] = 0;
	}
}

HuffmanEncodeDecode::~HuffmanEncodeDecode() {

}

void HuffmanEncodeDecode::computeCharCounts(ifstream& input, int* charCounts) {
	char character;

	if (input.is_open()) {
		while (input.good()) {
			input.get(character);
			charCounts[character]++;
		}
	}
}

void HuffmanEncodeDecode::printCountArray(ofstream& output) {
	try {
		for (int i = 0; i < 256; i++) {
			if (charCountsArray[i] > 0) {
				output << (char)i << " " << charCountsArray[i] << "\n";
			}
		}
	}
	catch (exception const& e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void HuffmanEncodeDecode::Encode(HuffmanBinaryTree* tree, ifstream& input, ofstream& output) {
	char inputCharacter;
	int index;
	string code = "";

	try{
		while (!input.eof()) {
			input.get(inputCharacter);
			index = (int)inputCharacter;
			code = tree->charCodes[index];
			output << code;
		}
	}
	catch (exception const& e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void HuffmanEncodeDecode::Decode(HuffmanBinaryTree* tree, ifstream& input, ofstream& output, TreeNode* treeRoot) {
	char oneBit;
	TreeNode* spot = treeRoot;

	try{
		while (!input.eof()) {
			if (tree->isLeaf(spot)) {
				output << spot->getCharacter();
				spot = treeRoot;
			}
			input.get(oneBit);
			if (oneBit == '0') {
				spot = spot->getLeft();
			}
			else if (oneBit == '1') {
				spot = spot->getRight();
			}
			else {
				cout << "Error! The compressed file is damaged." << endl;
				exit(0);
			}
		}
		if (input.eof() && tree->isLeaf(spot)==false) {
			cout << "Error! The compressed file is damaged." << endl;
		}
	}
	catch (exception const& e) {
		cout << "There is an error: " << e.what() << endl;
	}
}

void HuffmanEncodeDecode::userInterface(HuffmanBinaryTree* tree) {
	string originalFileName, compressedFileName, decompressedFileName;
	char yesNo = ' ';
	while (true) {
		cout << "Enter 'Y' to comress file, or 'N' to exit the program : ";
		cin >> yesNo;

		yesNo = toupper(yesNo);

		if (yesNo == 'N') {
			cout << "Exiting the program";
			exit(0);
		}
		if (yesNo == 'Y') {
			try {

				cout << "Enter file name to be compresses (including extension): ";
				cin >> originalFileName;
		;
				compressedFileName = originalFileName.substr(0, originalFileName.find_last_of('.')) + "_Compressed.txt";
				decompressedFileName = originalFileName.substr(0, originalFileName.find_last_of('.')) + "_Decompressed.txt";

				ifstream originalFile;
				ofstream compressedFile;
				ofstream decompressedFile;
				originalFile.open(originalFileName);
				compressedFile.open(compressedFileName);
				decompressedFile.open(decompressedFileName);

				Encode(tree, originalFile, compressedFile);
				cout << "File is compressed" << endl;
				
				originalFile.close();
				compressedFile.close();

				ifstream alreadyCompressedFile;
				alreadyCompressedFile.open(compressedFileName);
				Decode(tree, alreadyCompressedFile, decompressedFile, tree->getRoot());
				
				alreadyCompressedFile.close();
				decompressedFile.close();				
			}
			catch (exception const& e) {
				cout << "There is an error: " << e.what() << endl;
			}
		}
	}
}