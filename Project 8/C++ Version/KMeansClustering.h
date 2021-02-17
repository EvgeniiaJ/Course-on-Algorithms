#pragma once
#include <fstream>
#include <iostream>
#include "Point.h"

using namespace std;

class KMeansClustering {
private:
	int numRows;
	int numCols;
	int numberOfPoints;
	int changeCounter;
	int kClusters;

public:
	int** imageArray;
	Point* pointSet;
	Point* kCentroids;

	KMeansClustering(ifstream&, int);

	void initArrays();

	void loadPointSet(ifstream&, Point*);

	void assignLabel(Point*, int);

	void kMeansClustering(ofstream& output, Point*, int);

	void computeCentroids(Point*, Point*);

	void distanceMinLabel(Point, Point*);

	double computeDistance(Point, Point);

	void pointImageConversion(Point*, int**);

	void printImage(int**, ofstream&, int);
};