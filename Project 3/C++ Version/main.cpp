#include <iostream>
#include <string>
#include <fstream>

#include "TreeNode.h"
#include "TreeList.h"
#include "HuffmanBinaryTree.h"
using namespace std;

int main(int argc, char** argv) {

	ifstream input;
	ofstream debuging;
	ofstream codes;
	ofstream traversals;

	try {

		
		input.open(argv[1]);
		debuging.open(argv[2]);
		codes.open(argv[3]);
		traversals.open(argv[4]);
		

		TreeList* list = new TreeList();
		HuffmanBinaryTree* tree = new HuffmanBinaryTree();

		tree->constructHuffmanLinkedList(list, input, debuging);
		tree->constructHuffmanBinaryTree(list, debuging);
		tree->constructCodes(tree->getRoot(), "", codes);
		
		traversals << "Pre-Order Traversal of The Huffman Binary Tree:\n";
		tree->preOrderTraversal(tree->getRoot(), traversals);
		traversals << "\n\nIn-Order Traversal of The Huffman Binary Tree:\n";
		tree->inOrderTraversal(tree->getRoot(), traversals);
		traversals << "\n\nPost-Order Traversal of The Huffman Binary Tree:\n";
		tree->postOrderTraversal(tree->getRoot(), traversals);

		input.close();
		debuging.close();
		codes.close();
		traversals.close();

	}
	catch(exception e){
		cout << "There is an error: " << e.what();
	}

	return 0;
}
