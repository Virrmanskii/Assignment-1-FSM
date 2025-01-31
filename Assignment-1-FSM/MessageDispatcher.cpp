#include "MessageDispatcher.h"

void MessageDispatcher::discharge(Agent* reciever, const Telegram& msg)
{
	reciever->handleMessage(msg);
}

MessageDispatcher* MessageDispatcher::instance()
{
	static MessageDispatcher mDispatcher;
	return &mDispatcher;
}

void MessageDispatcher::dispatchMessage(double delay, int sender, int reciever, int msg, void* extraInfo)
{
	Agent* mReciever = AgentManager::instance()->getEntityFromID(reciever);
	Telegram telegram(sender, reciever, msg, 0.0, extraInfo);

	if (delay <= 0.0)
	{
		discharge(mReciever, telegram);
	}
	else
	{
		double currentTime = Timer::instance().getTime();

		telegram.dispatchTime = currentTime + delay;
		//messageQ.insert(telegram);
	}
}

void MessageDispatcher::dispatchDelayedMessage()
{
}
