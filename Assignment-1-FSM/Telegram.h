#pragma once

struct Telegram
{
	int sender;
	int reciever;
	int msg;
	double dispatchTime;
	double timeDisplacement;

	Telegram(int s, int r, int message, double dT, double td)
	{
		this->sender = s;
		this->reciever = r;
		this->msg = message;
		this->dispatchTime = dT;
		this->timeDisplacement = td;
	}
};