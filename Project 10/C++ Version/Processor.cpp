#include "Processor.h"
Processor::Processor(){
	this->doWhichJob = -1;
	this->timeRemain = 0;
}

Processor::Processor(int doWhichJob, int timeRemain) {
	this->doWhichJob = doWhichJob;
	this->timeRemain = timeRemain;
}

int Processor::getDoWhichJob() {
	return this->doWhichJob;
}

void Processor::setDoWhichJob(int doWhichJob) {
	this->doWhichJob = doWhichJob;
}

int Processor::getTimeRemain() {
	return this->timeRemain;
}

void Processor::setTimeRemain(int timeRemain) {
	this->timeRemain = timeRemain;
}
