#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"

template <typename EntityType, typename StateType>
class WalkState : public State2<EntityType, StateType>
{
public:
	WalkState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
};

template<typename EntityType, typename StateType>
inline WalkState<EntityType, StateType>::WalkState()
{
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::enter(EntityType* e)
{
	std::cout << Timer::instance().getTimeString() << e->getName() << ": Starts walking" << std::endl;
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::execute(EntityType* e)
{
	std::cout << Timer::instance().getTimeString() << e->getName() << ": Walking" << std::endl;
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::exit(EntityType* e)
{
	std::cout << Timer::instance().getTimeString() << e->getName() << ": Stops walking" << std::endl;
}
