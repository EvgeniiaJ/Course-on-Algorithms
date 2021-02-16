#pragma once
#include <fstream>

#include "TreeNode.h"
#include "TreeList.h"
#include "HuffmanBinaryTree.h"


using namespace std;

class HuffmanEncodeDecode {
public:
	int* charCountsArray;

	HuffmanEncodeDecode();

	~HuffmanEncodeDecode();

	void computeCharCounts(ifstream&, int*);

	void printCountArray(ofstream&);

	void Encode(HuffmanBinaryTree*, ifstream&, ofstream&);

	void Decode(HuffmanBinaryTree*, ifstream&, ofstream&, TreeNode*);

	void userInterface(HuffmanBinaryTree*);

};