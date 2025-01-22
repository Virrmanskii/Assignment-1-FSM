#include "Work.h"

Work::Work(WorkType job)
{
	this->activeJob = job;
	updateJobIntensity(); 
}

void Work::setActiveJob(WorkType newJob)
{
	this->activeJob = newJob;
	updateJobIntensity();
}

WorkType Work::getActiveJob()
{
	return this->activeJob;
}

const char* Work::getActiveJobEnterLine()
{
	const char* vLine = "";

	switch (this->activeJob)
	{
	case WorkType::Miner:
		vLine = "Enters mine and starts mining";
		break;

	case WorkType::Fisher:
		vLine = "Enters wharf and starts fishing";
		break;
	default:
		vLine = "";
		break;
	}
	return vLine;
}

const char* Work::getActiveJobExecuteLine()
{
	const char* vLine = "";

	switch (this->activeJob)
	{
	case WorkType::Miner:
		vLine = "Mining";
		break;

	case WorkType::Fisher:
		vLine = "Fishing";
		break;
	default:
		vLine = "";
		break;
	}
	return vLine;
}

const char* Work::getActiveJobExitLine()
{
	const char* vLine = "";

	switch (this->activeJob)
	{
	case WorkType::Miner:
		vLine = "Stops mining and leavs the mine";
		break;

	case WorkType::Fisher:
		vLine = "Stops fishing and leaves the wharf";
		break;
	default:
		vLine = "";
		break;
	}
	return vLine;
}

int Work::getJobIntensity()
{
	return this->jobIntensity;
}

void Work::updateJobIntensity()
{
	int newValue = 0;

	switch (this->activeJob)
	{
	case WorkType::Miner:
		newValue = 4;
		break;

	case WorkType::Fisher:
		newValue = 1;
		break;
	default:
		break;
	}
	this->jobIntensity = newValue;
}
