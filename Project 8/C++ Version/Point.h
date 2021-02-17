#pragma once
class Point{
private:
	double xCoordinate;
	double yCoordinate;
	int label;
	double distance;
public:
	Point();

	Point(double, double, int, double);

	double getXCoordinate();

	void setXCoordinate(double);

	double getYCoordinate();

	void setYCoordinate(double);

	double getLabel();

	void setLabel(int);

	double getDistance();

	void setDistance(double);

};

