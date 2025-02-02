#include "MessageDispatcher.h"

void MessageDispatcher::discharge(BaseGameEntity* reciever, const Telegram& msg)
{
	reciever->handleMessage(msg);
}

MessageDispatcher* MessageDispatcher::instance()
{
	static MessageDispatcher mDispatcher;
	return &mDispatcher;
}

void MessageDispatcher::dispatchMessage(double delay, int sender, int reciever, int msg, double td)//, void* extraInfo
{
	BaseGameEntity* mReciever = AgentManager::instance()->getEntityFromID(reciever);
	Telegram telegram(sender, reciever, msg, 0.0, td);//, extraInfo

	if (delay <= 0.0)
	{
		discharge(mReciever, telegram);
	}
	else
	{
		double currentTime = Timer::instance().getTime();

		telegram.dispatchTime = currentTime + delay;
		messageQ.insert(telegram);
	}
}

void MessageDispatcher::dispatchDelayedMessage()
{
	double currentTime = Timer::instance().getTime(); 

	while (!this->messageQ.empty() && (this->messageQ.begin()->dispatchTime < currentTime) && (this->messageQ.begin()->dispatchTime > 0.0))
	{
		Telegram telegram = *messageQ.begin();
		BaseGameEntity* reciever = AgentManager::instance()->getEntityFromID(telegram.reciever);
		discharge(reciever, telegram);
		messageQ.erase(messageQ.begin());
	}
}
