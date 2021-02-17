#include <iostream>
#include <fstream>
#include <string>

#include "Point.h"
#include "KMeansClustering.h"

using namespace std;

int main(int argc, char** argv) {

	string inputFileName = argv[1];
	string outputFileName = argv[2];
	int kValue = -1;
	ifstream input;
	ofstream output;

	try {
		
		input.open(inputFileName);
		output.open(outputFileName);

		cout << "Enter a value for k (number of clusters to split data points into): ";
		cin >> kValue;
		output << "\t\t\tK Means Clustering with " << kValue << " clusters: " << endl;

		KMeansClustering* clustering = new KMeansClustering(input, kValue);
		clustering->loadPointSet(input, clustering->pointSet);
		clustering->kMeansClustering(output, clustering->pointSet, kValue);

		input.close();
		output.close();
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
	return 0;
}
