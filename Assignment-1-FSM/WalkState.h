#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"
#include "Constants.h"
#include "MessageDispatcher.h"
#include "AgentManager.h"

template <typename EntityType, typename StateType>
class WalkState : public State2<EntityType, StateType>
{
public:
	int walktick = 0;

	WalkState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline WalkState<EntityType, StateType>::WalkState()
{
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::enter(EntityType* e)
{
	e->setLocation(LocationType::TRAVELING);
	const char* reasonLine = "";

	switch (e->getAgentStateMachine()->getPreviousState()->stateChangeReason)
	{
	case WORKING:
		reasonLine = "to work ";
		break;
	case EATING:
		reasonLine = "home ";
		break;
	case DRINKING:
		reasonLine = "home "; 
		break;
	case SLEEPING:
		reasonLine = "home "; 
		break;
	case BUYING:
		reasonLine = "to the store ";
		break;
	case SELLING:
		break;
	case WALKING:
		break;
	case SOCIALIZE:
		break;
	default:
		break;
	}

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Starts walking " << reasonLine << std::endl;
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::execute(EntityType* e)
{
	double time = Timer::instance().getTime();

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Walking" << std::endl;
	this->walktick += 1;

	if (this->walktick == 3)
	{
		this->stateChangeReason = e->getAgentStateMachine()->getPreviousState()->stateChangeReason;
		e->changeState(e->getAgentStateMachine()->states.at(e->getAgentStateMachine()->getPreviousState()->stateChangeReason));
	}
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::exit(EntityType* e)
{
	const char* locationLine = "";

	switch (this->stateChangeReason)
	{
	case WORKING:
		locationLine = "work";
		break;
	case EATING:
		locationLine = "home";
		break;
	case DRINKING:
		locationLine = "home";
		break;
	case SLEEPING:
		locationLine = "home";
		break;
	case BUYING:
		locationLine = "store";
		break;
	case SELLING:
		break;
	case WALKING:
		break;
	case SOCIALIZE:
		locationLine = "activity centre";
		break;
	default:
		break;
	}

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Arrives at " << locationLine << std::endl;
	this->walktick = 0;
}

template<typename EntityType, typename StateType>
inline bool WalkState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
{
	switch (msg.msg)
	{
	case Message::TIME_TO_SOCIALIZE:

		if (entity->canSocialize())
		{
			MessageDispatcher::instance()->dispatchMessage(0.0, entity->ID(), entity->ID(), Message::CAN_SOCIALIZE, 0.0);
		}
		else
		{
			std::cout << Timer::instance().getTimeString() << entity->getName() << ": Aww i can't come\n";
		}

		return true;
		break;

	case Message::CAN_SOCIALIZE:
		std::cout << Timer::instance().getTimeString() << entity->getName() << ": Oh right, time to hang out\n";
		entity->getAgentStateMachine()->getCurrentState()->stateChangeReason = AgentState::SOCIALIZE;
		entity->changeState(entity->getAgentStateMachine()->states.at(WALKING));

		return true;
		break;
	case Message::WANT_TO_SOCIALIZE:
		std::cout << Timer::instance().getTimeString() << entity->getName() << ": Of course i want to hang out at " << Timer::instance().getTimeString(msg.timeDisplacement) << "\n";
		MessageDispatcher::instance()->dispatchMessage(msg.timeDisplacement, entity->ID(), entity->ID(), Message::TIME_TO_SOCIALIZE, 0.0);
		MessageDispatcher::instance()->dispatchMessage(msg.timeDisplacement, entity->ID(), msg.sender, Message::TIME_TO_SOCIALIZE, 0.0);
		return true;
		break;

	default:
		break;
	}
	return false;
}
