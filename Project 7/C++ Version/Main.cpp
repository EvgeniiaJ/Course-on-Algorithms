#include <iostream>
#include <fstream>

#include "TreeNode.h"
#include "TreeList.h"
#include "HuffmanBinaryTree.h"
#include "HuffmanEncodeDecode.h"

using namespace std;

int main(int argc, char** argv) {

	string inputFileString = argv[1];
	string debugFileString = inputFileString.substr(0, inputFileString.find_last_of('.')) + "_Debug.txt";

	try {
		ifstream input;
		ofstream debug;

		input.open(inputFileString);
		debug.open(debugFileString);

		HuffmanEncodeDecode* encodeDecode = new HuffmanEncodeDecode();
		encodeDecode->computeCharCounts(input, encodeDecode->charCountsArray);
		encodeDecode->printCountArray(debug);
		input.close();

		HuffmanBinaryTree* tree = new HuffmanBinaryTree();
		tree->constructHuffmanLinkedList(encodeDecode->charCountsArray, debug);
		tree->constructHuffmanBinaryTree(tree->list, debug);
		tree->constructCodes(tree->getRoot(), "");
		debug << "\nOutput with codes:\n";
		tree->list->printList(tree->list->getListHead(), debug);

		debug << "\nTraversals:\n";
		debug << "Pre-Order Traversal:\n";
		tree->preOrderTraversal(tree->getRoot(), debug);
		debug << "\n\nIn-Order Traversal:\n";
		tree->inOrderTraversal(tree->getRoot(), debug);
		debug << "\n\nPost-Order Traversal:\n";
		tree->postOrderTraversal(tree->getRoot(), debug);

		encodeDecode->userInterface(tree);
		
		debug.close();

	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
	return 0;
}