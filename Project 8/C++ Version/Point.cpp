#include "Point.h"

Point::Point(){
	this->xCoordinate = 0.0;
	this->yCoordinate = 0.0;
	this->label = 0;
	this->distance = 99999.0;
}

Point::Point(double xCoordinate, double yCoordinate, int label, double distance){
	this->xCoordinate = xCoordinate;
	this->yCoordinate = yCoordinate;
	this->label = label;
	this->distance = distance;
}

double Point::getXCoordinate(){
	return xCoordinate;
}

void Point::setXCoordinate(double xCoordinate){
	this->xCoordinate = xCoordinate;
}

double Point::getYCoordinate(){
	return yCoordinate;
}

void Point::setYCoordinate(double yCoordinate){
	this->yCoordinate = yCoordinate;
}

double Point::getLabel(){
	return label;
}

void Point::setLabel(int label){
	this->label = label;
}

double Point::getDistance(){
	return distance;
}

void Point::setDistance(double distance){
	this->distance = distance;
}
