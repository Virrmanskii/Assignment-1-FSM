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

	if (e->getDrinkTimer() <= time && e->getWater() > 0 && e->getThirst() > 40)
	{
		e->setDrinkTimer(time + e->getDrinkCD());
		e->setWater(-1);
		e->decreaseThirst(40);
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Drinking" << std::endl;
	}
}     

template<typename EntityType, typename StateType>
inline void DrinkState<EntityType, StateType>::exit(EntityType* e)
{
}
