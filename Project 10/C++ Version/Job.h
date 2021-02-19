#pragma once
class Job{

private:
	int jobTime;
	int onWhichProcessor;
	int onOpen;
	int parentCounter;
	int dependentCounter;

public:

	Job();

	Job(int, int, int, int, int);

	int getJobTime();

	void setJobTime(int);

	int getOnWhichProcessor();

	void setOnWhichProcessor(int);

	int getOnOpen();

	void setOnOpen(int);

	int getParentCounter();

	void setParentCounter(int);

	int getDependentCounter();

	void setDependentCounter(int);
};

