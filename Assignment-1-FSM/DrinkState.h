#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"
#include "Constants.h"
#include "MessageDispatcher.h"
#include "AgentManager.h"

template <typename EntityType, typename StateType>
class DrinkState : public State2<EntityType, StateType>
{
public:

	DrinkState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline DrinkState<EntityType, StateType>::DrinkState()
{
}

template<typename EntityType, typename StateType>
inline void DrinkState<EntityType, StateType>::enter(EntityType* e)
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
	if (e->getWater() > 0)
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Finds something to drink " << std::endl;
	}
	else
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Finds nothing to drink " << std::endl;
		//TODO change to store state to buy water
	}
}

template<typename EntityType, typename StateType>
inline void DrinkState<EntityType, StateType>::execute(EntityType* e)
{
	double time = Timer::instance().getTime();

	if (e->getDrinkTimer() <= time && e->getWater() > 0 && e->getThirst() > 20)
	{
		e->setDrinkTimer(time + e->getDrinkCD());
		e->setWater(-1);
		e->decreaseThirst(20);
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Drinking" << std::endl;
	}

	//if (e->getThirst() < 10)
	
	if (e->getHunger() > 40 && e->getFood() > 0) 
	{
		//TODO change to eating statethis->stateChangeReason = BUYING; 
		this->stateChangeReason = EATING;
		e->changeState(e->getAgentStateMachine()->states.at(EATING));
		return;
	}
	if (e->getFatigue() >= 100)
	{
		//TODO change to sleep state
		this->stateChangeReason = SLEEPING;
		e->changeState(e->getAgentStateMachine()->states.at(SLEEPING));
		return;
	}
	if (e->getWater() <= 2)
	{
		this->stateChangeReason = BUYING;
		e->changeState(e->getAgentStateMachine()->states.at(WALKING));
		return;
	}
	//if (e->getHunger() e->getFatigue())
	//{

	//}
	//this->stateChangeReason = WORKING;
	//e->changeState(e->getAgentStateMachine()->states.at(WORKING));
	
}     

template<typename EntityType, typename StateType>
inline void DrinkState<EntityType, StateType>::exit(EntityType* e)
{
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
	//std::cout << Timer::instance().getTimeString() << e->getName() << ": " << std::endl;
}

template<typename EntityType, typename StateType>
inline bool DrinkState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
{
	switch (msg.msg)
	{
	case Message::TIME_TO_SOCIALIZE:

		if (entity->canSocialize())
		{
			//entity->getAgentStateMachine()->getCurrentState()->stateChangeReason = AgentState::SOCIALIZE;
			//entity->changeState(entity->getAgentStateMachine()->states.at(WALKING));
			MessageDispatcher::instance()->dispatchMessage(0.0, entity->ID(), entity->ID(), Message::CAN_SOCIALIZE, 0.0);
		}
		else
		{
			std::cout << Timer::instance().getTimeString() << entity->getName() << ": Aww i can't come----------------------------------------------------------------------------------------------\n";
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
