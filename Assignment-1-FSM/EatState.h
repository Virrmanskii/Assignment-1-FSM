#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"
#include "Constants.h"
#include "MessageDispatcher.h"
#include "AgentManager.h"

template <typename EntityType, typename StateType>
class EatState : public State2<EntityType, StateType>
{
public:

	EatState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline EatState<EntityType, StateType>::EatState()
{
}

template<typename EntityType, typename StateType>
inline void EatState<EntityType, StateType>::enter(EntityType* e)
{
	e->setLocation(LocationType::HOME);

	switch (this->stateChangeReason)
	{
	case WORKING:
		break;
	case EATING:
		break;
	case DRINKING:
		break;
	case SLEEPING:
		break;
	case BUYING:
		break;
	case SELLING:
		break;
	case WALKING:
		break;
	case SOCIALIZE:
		break;
	case DEAD:
		break;
	default:
		break;
	}
	if (e->getFood() > 0)
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Finds food " << std::endl;
	}
	else
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Finds no food " << std::endl;
		//TODO change to store state to buy food
	}
}

template<typename EntityType, typename StateType>
inline void EatState<EntityType, StateType>::execute(EntityType* e)
{
	double time = Timer::instance().getTime();


	if (e->getFood() > 0 && e->getHunger() > 20)
	{
		e->setFood(-1);
		e->decreaseHunger(30);
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Eating" << std::endl;
	}
	
	if (e->getThirst() > 30 && e->getWater() > 0)
	{
		this->stateChangeReason = DRINKING;
		e->changeState(e->getAgentStateMachine()->states.at(DRINKING));
		return;
	}
	if (e->getFatigue() >= 100)
	{
		//TODO change to sleep state
		this->stateChangeReason = SLEEPING;
		e->changeState(e->getAgentStateMachine()->states.at(SLEEPING));
		return;
	}
	if (e->getFood() <= 2)
	{
		this->stateChangeReason = BUYING;
		e->changeState(e->getAgentStateMachine()->states.at(WALKING));
		return;
	}
	
}

template<typename EntityType, typename StateType>
inline void EatState<EntityType, StateType>::exit(EntityType* e)
{
	const char* reasonLine = "";

	switch (this->stateChangeReason)
	{
	case WORKING:
		break;
	case EATING:
		reasonLine = "";
		break;
	case DRINKING:
		reasonLine = "";
		break;
	case SLEEPING:
		//Should not handle
		break;
	case BUYING:
		reasonLine = "Buy food";
		break;
	case SELLING:
		break;
	case WALKING:
		break;
	case SOCIALIZE:
		reasonLine = "";
		break;
	default:
		break;
	}
}

template<typename EntityType, typename StateType>
inline bool EatState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
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
