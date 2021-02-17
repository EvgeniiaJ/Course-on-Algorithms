#include "KMeansClustering.h"

KMeansClustering::KMeansClustering(ifstream& input, int kClusters){
	input >> this->numRows;
	input >> this->numCols;
	input >> this->numberOfPoints;
	this->changeCounter = 0;
	this->kClusters = kClusters;
	initArrays();
}

void KMeansClustering::initArrays(){
	imageArray = new int* [numRows];
	for (int i = 0; i < numRows; i++) {
		imageArray[i] = new int[numCols];
		for (int j = 0; j < numCols; j++) {
			imageArray[i][j] = 0;
		}
	}

	pointSet = new Point[numberOfPoints];

	for (int i = 0; i < numberOfPoints; i++) {
		pointSet[i] = Point(0.0, 0.0, 0, 99999.0);
	}

	kCentroids = new Point[kClusters + 1];

	for (int i = 0; i <= kClusters; i++) {
		kCentroids[i] = Point(0.0, 0.0, 0, 0.0);
	}
}

void KMeansClustering::loadPointSet(ifstream& input, Point* pointSet){
	int index = 0;
	int x, y;

	while (!input.eof()) {
		input >> x;
		input >> y;
		pointSet[index].setXCoordinate((double)x);
		pointSet[index].setYCoordinate((double)y);
		index++;
	}
}

void KMeansClustering::assignLabel(Point* pointSet, int kNumber){
	int front = 0;
	int back = numberOfPoints - 1;
	int label = 1;

	while (front <= back) {
		if (label > kNumber) {
			label = 1;
		}
		
		else if (label == kNumber) {
			pointSet[front].setLabel(label);
			front++;
			label++;
			pointSet[back].setLabel(1);
			back--;
		}

		else {
			pointSet[front].setLabel(label);
			front++;
			label++;
			pointSet[back].setLabel(label);
			back--;
			label++;
		}

	}
}

void KMeansClustering::kMeansClustering(ofstream& output, Point* pointSet, int kNumber){
	int iteration = 0;
	assignLabel(pointSet, kNumber);
	changeCounter = 0;
	
	while (true) {
		pointImageConversion(pointSet, imageArray);
		printImage(imageArray, output, iteration);
		changeCounter = 0;
		computeCentroids(pointSet, kCentroids);
		int index = 0;
		while (index < numberOfPoints) {
			distanceMinLabel(pointSet[index], kCentroids);
			index++;
		}
		if (changeCounter == 0) {
			break; 
		}
		iteration++;
	}

}

void KMeansClustering::computeCentroids(Point* pointSet, Point* kCentroids){
	double* sumOfX = new double[kClusters + 1];
	double* sumOfY = new double[kClusters + 1];
	double* totalPoints = new double[kClusters + 1];

	for (int i = 0; i <= kClusters; i++) {
		sumOfX[i] = 0.0;
		sumOfY[i] = 0.0;
		totalPoints[i] = 0.0;
	}

	int index = 0;
	int label = 0;

	while (index < numberOfPoints) {
		label = pointSet[index].getLabel();
		sumOfX[label] += pointSet[index].getXCoordinate();
		sumOfY[label] += pointSet[index].getYCoordinate();
		totalPoints[label]++;
		index++;
	}

	label = 1;

	while (label <= kClusters) {
		kCentroids[label].setXCoordinate(sumOfX[label] / totalPoints[label]);
		kCentroids[label].setYCoordinate(sumOfY[label] / totalPoints[label]);
		label++;
	}
}

void KMeansClustering::distanceMinLabel(Point point, Point* kCentroids){
	double minDistance = 99999.0;
	int minLabel = 0;
	int label = 1;
	while (label <= kClusters) {
		double distance = computeDistance(point, kCentroids[label]);
		if (distance < minDistance) {
			minDistance = distance;
			minLabel = label;
		}
		label++;
	}

	if (minDistance < point.getDistance()) {
		point.setDistance(minDistance);
		point.setLabel(minLabel);
		changeCounter++;
	}
}

double KMeansClustering::computeDistance(Point point, Point kPoint){
	double xDistance = pow(kPoint.getXCoordinate() - point.getXCoordinate(), 2);
	double yDistance = pow(kPoint.getYCoordinate() - point.getYCoordinate(), 2);
	double distance = sqrt(xDistance + yDistance);
	return distance;
}

void KMeansClustering::pointImageConversion(Point* pointSet, int** imageArray){
	for (int i = 0; i < numberOfPoints; i++) {
		int x = (int)pointSet[i].getXCoordinate();
		int y = (int)pointSet[i].getYCoordinate();
		imageArray[x][y] = pointSet[i].getLabel();
	}
}

void KMeansClustering::printImage(int** imageArray, ofstream& output, int iteration){
	try {
		output << "Result of Iteration #" + iteration << endl;
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				if (imageArray[i][j] > 0) {
					output << imageArray[i][j] << " ";
				}
				else {
					output << " ";
				}
			}
			output << endl;
		}
		output << endl << endl;
	}
	catch (exception e) {
		cout << "There is an error: " << e.what() << endl;
	}
}
