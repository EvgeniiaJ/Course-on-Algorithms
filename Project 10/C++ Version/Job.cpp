#include "Job.h"

Job::Job(){
	this->jobTime = 0;
	this->onWhichProcessor = -1;
	this->onOpen = 0;
	this->parentCounter = 0;
	this->dependentCounter = 0;
}

Job::Job(int jobTime, int onWhichProcessor, int onOpen, int parentCounter, int dependentCounter) {
	this->jobTime = jobTime;
	this->onWhichProcessor = onWhichProcessor;
	this->onOpen = onOpen;
	this->parentCounter = parentCounter;
	this->dependentCounter = dependentCounter;
}

int Job::getJobTime() {
	return this->jobTime;
}

void Job::setJobTime(int jobTime) {
	this->jobTime = jobTime;
}

int Job::getOnWhichProcessor() {
	return this->onWhichProcessor;
}

void Job::setOnWhichProcessor(int onWhichProcessor) {
	this->onWhichProcessor = onWhichProcessor;
}

int Job::getOnOpen() {
	return onOpen;
}

void Job::setOnOpen(int onOpen) {
	this->onOpen = onOpen;
}

int Job::getParentCounter() {
	return this->parentCounter;
}

void Job::setParentCounter(int parentCounter) {
	this->parentCounter = parentCounter;
}

int Job::getDependentCounter() {
	return this->dependentCounter;
}

void Job::setDependentCounter(int dependentCounter) {
	this->dependentCounter = dependentCounter;
}
