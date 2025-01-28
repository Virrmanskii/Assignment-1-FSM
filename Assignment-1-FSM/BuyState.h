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
};

template<typename EntityType, typename StateType>
inline BuyState<EntityType, StateType>::BuyState()
{

}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::enter(EntityType* e)
{
	std::cout << Timer::instance().getTimeString() << e->getName() << ": Enters the store" << std::endl;
}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::execute(EntityType* e)
{

}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::exit(EntityType* e)
{
}
