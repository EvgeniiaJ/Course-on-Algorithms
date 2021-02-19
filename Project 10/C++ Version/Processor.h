#pragma once
class Processor{

private:
	int doWhichJob;
	int timeRemain;

public:

	Processor();

	Processor(int, int);

	int getDoWhichJob();

	void setDoWhichJob(int);

	int getTimeRemain();

	void setTimeRemain(int);

};

