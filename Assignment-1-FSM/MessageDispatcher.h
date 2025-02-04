#pragma once
#include "Constants.h"
#include "AgentManager.h"
#include "BaseGameEntity.h"
#include "Telegram.h"
#include "Time.h"
#include "set"

struct CompareTelegram
{
    bool operator()(const Telegram& lhs, const Telegram& rhs) const
    {
        // First, compare dispatchTime
        if (lhs.dispatchTime != rhs.dispatchTime)
        {
            return lhs.dispatchTime < rhs.dispatchTime;
        }
        // If dispatchTime is the same, compare sender
        if (lhs.sender != rhs.sender) 
        {
            return lhs.sender < rhs.sender;
        }
        // If sender is the same, compare receiver
        if (lhs.reciever != rhs.reciever) 
        {
            return lhs.reciever < rhs.reciever;
        }
        // If receiver is the same, compare msg
        return lhs.msg < rhs.msg;
    }
};

class MessageDispatcher
{
private:
	std::set<Telegram, CompareTelegram> messageQ;
	void discharge(BaseGameEntity* reciever, const Telegram& msg);

	MessageDispatcher() {};

public:
	static MessageDispatcher* instance();
	void dispatchMessage(double delay, int sender, int reciever, int msg, double td);
	void dispatchDelayedMessage();
};

