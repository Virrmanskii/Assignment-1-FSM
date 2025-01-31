#pragma once

struct Telegram
{
	int sender;
	int reciever;
	int msg;
	double dispatchTime;
	//void* extraInfo;
	Telegram(int s, int r, int message, double dT)//, void* eI
	{
		this->sender = s;
		this->reciever = r;
		this->msg = message;
		this->dispatchTime = dT;
		//this->extraInfo = eI;
	}
};