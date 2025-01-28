#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"

template <typename EntityType, typename StateType>
class EatState : public State2<EntityType, StateType>
{
public:

	EatState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
};

template<typename EntityType, typename StateType>
inline EatState<EntityType, StateType>::EatState()
{
}

template<typename EntityType, typename StateType>
inline void EatState<EntityType, StateType>::enter(EntityType* e)
{
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

	if (e->getFood() == 0 && e->getJobResource() > 3) 
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Can't find any food " << std::endl;
		this->stateChangeReason = BUYING; 
		e->changeState(e->getAgentStateMachine()->states.at(WALKING));
	}

	if (e->getEatTimer() <= time && e->getFood() > 0 && e->getHunger() > 20)
	{
		std::cout << e->getHunger() << std::endl;
		e->setEatTimer(time + e->getEatCD());
		e->setFood(-1);
		e->decreaseHunger(30);
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Eating" << std::endl;
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

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Leaves home to " << reasonLine << std::endl;
}
