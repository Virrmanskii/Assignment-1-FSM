#pragma once
#include <iostream>

enum WorkType
{
	Miner,
	Fisher
};

class Work
{
public:
	Work() {};
	Work(WorkType job);
	~Work() {};
	void setActiveJob(WorkType newJob);
	WorkType getActiveJob();
	const char* getActiveJobEnterLine();
	const char* getActiveJobExecuteLine();
	const char* getActiveJobExitLine();
	const char* getResourceString();
	int getActiveJobResourceAmount();
	int getResourceValue();
	int getJobIntensity();

private:
	WorkType activeJob;
	int jobIntensity;

	void updateJobIntensity();
};

