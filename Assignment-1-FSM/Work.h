#pragma once
#include <iostream>
#include "Constants.h"

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
	LocationType getWorkLocation();

private:
	WorkType activeJob;
	int jobIntensity;

	void updateJobIntensity();
};

