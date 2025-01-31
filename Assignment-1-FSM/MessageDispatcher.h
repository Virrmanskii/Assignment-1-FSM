#pragma once
#include "Constants.h"
#include "AgentManager.h"
#include "Telegram.h"
#include "Time.h"
#include "set"
//#include "Agent.h"


class MessageDispatcher
{
private:
	//std::set<Telegram> messageQ;
	void discharge(Agent* reciever, const Telegram& msg);

	MessageDispatcher() {};

public:
	static MessageDispatcher* instance();
	void dispatchMessage(double delay, int sender, int reciever, int msg, void* extraInfo);
	void dispatchDelayedMessage();
};

