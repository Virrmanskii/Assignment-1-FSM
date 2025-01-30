#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"

template <typename EntityType, typename StateType>
class DrinkState : public State2<EntityType, StateType>
{
public:

	DrinkState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
};

template<typename EntityType, typename StateType>
inline DrinkState<EntityType, StateType>::DrinkState()
{
}

template<typename EntityType, typename StateType>
inline void DrinkState<EntityType, StateType>::enter(EntityType* e)
{
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
	
	if (e->getHunger() > 40) 
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
}
