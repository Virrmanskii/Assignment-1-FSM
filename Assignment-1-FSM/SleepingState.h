#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"
#include "Constants.h"
#include "MessageDispatcher.h"
#include "AgentManager.h"

template <typename EntityType, typename StateType>
class SleepingState : public State2<EntityType, StateType>
{
public:
	SleepingState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline SleepingState<EntityType, StateType>::SleepingState()
{
}

template<typename EntityType, typename StateType>
inline void SleepingState<EntityType, StateType>::enter(EntityType* e)
{
	e->setLocation(LocationType::HOME);
	const char* reasonLine = "";

	switch (e->getAgentStateMachine()->getPreviousState()->stateChangeReason)
	{
	case WORKING:
		
		break;
	case EATING:
		break;
	case DRINKING:
		break;
	case SLEEPING:
		reasonLine = "Enters the home to sleep";
		break;
	case BUYING:
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

	std::cout << Timer::instance().getTimeString() << e->getName() << ": "  << reasonLine << std::endl;
}

template<typename EntityType, typename StateType>
inline void SleepingState<EntityType, StateType>::execute(EntityType* e)
{
	double time = Timer::instance().getTime();

	if (e->isDead())
	{
		this->stateChangeReason = DEAD;
		e->changeState(e->getAgentStateMachine()->states.at(DEAD));
		return;
	}

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Sleeping" << std::endl;
	e->decreaseFatigue(20);

	if (e->getThirst() >= 50)
	{
		this->stateChangeReason = DRINKING;
		e->changeState(e->getAgentStateMachine()->states.at(DRINKING));
		return;
	}

	if (e->getHunger() >= 50)
	{
		this->stateChangeReason = EATING;
		e->changeState(e->getAgentStateMachine()->states.at(EATING));
		return;
	}
}

template<typename EntityType, typename StateType>
inline void SleepingState<EntityType, StateType>::exit(EntityType* e)
{
	const char* reasonLine = "";

	switch (this->stateChangeReason)
	{
	case WORKING:
		break;
	case EATING:
		reasonLine = "to find something to eat";
		break;
	case DRINKING:
		reasonLine = "to find something to drink";
		break;
	case SLEEPING:
		//Should not handle
		break;
	case BUYING:
		break;
	case SELLING:
		break;
	case WALKING:
		break;
	case SOCIALIZE:
		reasonLine = "socialize";
		break;
	default:
		break;
	}

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Woke up to "  << reasonLine << std::endl;
}

template<typename EntityType, typename StateType>
inline bool SleepingState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
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
