#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"

template <typename EntityType, typename StateType>
class BuyState : public State2<EntityType, StateType>
{
public:

	BuyState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline BuyState<EntityType, StateType>::BuyState()
{

}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::enter(EntityType* e)
{
	e->setLocation(LocationType::HOME);
	std::cout << Timer::instance().getTimeString() << e->getName() << ": Enters the store" << std::endl;
}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::execute(EntityType* e)
{
	if (e->isDead())
	{
		this->stateChangeReason = DEAD;
		e->changeState(e->getAgentStateMachine()->states.at(DEAD));
		return;
	}

	if (e->isFatigued())
	{
		this->stateChangeReason = SLEEPING;
		e->changeState(e->getAgentStateMachine()->states.at(WALKING));
		return;
	}

	if (e->isThirsty())
	{
		this->stateChangeReason = DRINKING;
		e->changeState(e->getAgentStateMachine()->states.at(WALKING));
		return;
	}

	if (e->isHungry())
	{
		this->stateChangeReason = EATING;
		e->changeState(e->getAgentStateMachine()->states.at(WALKING));
		return;
	}

	if (e->getJobResource() > 0)	//Sälj om det finns resurser att sälja
	{
		int nr = 0;
		for (int i= 0; i < e->getJobResource(); i++)
		{
			nr += 1;
		}
		e->decreaseJobResource(nr);
		e->increaseMoney(nr * (e->getWork().getResourceValue()));
		std::cout << e->getFood() << std::endl;
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Sells " << nr << " " << e->getWork().getResourceString() << "and recieves "<< nr * (e->getWork().getResourceValue()) << "kr" << std::endl;
	}

	if (e->hasMoney())
	{
		if (e->getFood() + 1 > e->getWater())
		{
			if (e->getMoney() >= 10)
			{
				e->setWater(1);
				e->decreaseMoney(10);
				std::cout << Timer::instance().getTimeString() << e->getName() << ": Buys water" << std::endl;
				return;
			}
		}
		if (e->getMoney() >= 30)
		{
			e->setFood(1);
			e->decreaseMoney(30);
			std::cout << Timer::instance().getTimeString() << e->getName() << ": Buys food" << std::endl;
			return;
		}
		
	}
	else
	{
		this->stateChangeReason = WORKING;
		e->changeState(e->getAgentStateMachine()->states.at(WALKING));
	}




	
	//if (e->getMoney() > 10)
	//{
	//	if (e->getFood() <= 40 && e->getMoney() > 30)
	//	{
	//		e->setFood(1);
	//		e->decreaseMoney(30);
	//		std::cout << Timer::instance().getTimeString() << e->getName() << ": Buys food" << std::endl;
	//	}
	//	if (e->getFood() <= 40 && e->getMoney() > 10)
	//	{
	//		e->setWater(1);
	//		e->decreaseMoney(10);
	//		std::cout << Timer::instance().getTimeString() << e->getName() << ": Buys water" << std::endl;
	//	}
	//}
	//
	//if ((e->getHunger() < 70 || e->getThirst() < 60 || e->getFatigue() < 20) && e->getMoney() <= 10)
	//{
	//	std::cout << Timer::instance().getTimeString() << e->getName() << ": Is feeling great and is ready for work" << std::endl;
	//	this->stateChangeReason = WORKING;
	//	e->changeState(e->getAgentStateMachine()->states.at(WALKING));
	//	return;
	//}
	//if ((e->getHunger() < 70 || e->getThirst() < 60 || e->getFatigue() < 20) && e->getMoney() <= 10)
	//{
	//	this->stateChangeReason = WORKING;
	//	e->changeState(e->getAgentStateMachine()->states.at(WALKING));
	//	std::cout << Timer::instance().getTimeString() << e->getName() << ": Is feeling great and is ready for work" << std::endl;
	//}
}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::exit(EntityType* e)
{
	std::cout << Timer::instance().getTimeString() << e->getName() << ": Exits the store" << std::endl;
}

template<typename EntityType, typename StateType>
inline bool BuyState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
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
