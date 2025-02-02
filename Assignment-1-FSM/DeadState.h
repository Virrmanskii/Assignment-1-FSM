#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"

template <typename EntityType, typename StateType>
class DeadState : public State2<EntityType, StateType>
{
public:
	const char* deathTimeStamp;

	DeadState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline DeadState<EntityType, StateType>::DeadState()
{
}

template<typename EntityType, typename StateType>
inline void DeadState<EntityType, StateType>::enter(EntityType* e)
{
	this->deathTimeStamp = (Timer::instance().getTimeString()).c_str();
}

template<typename EntityType, typename StateType>
inline void DeadState<EntityType, StateType>::execute(EntityType* e)
{
	std::cout << Timer::instance().getTimeString() << e->getName() << ": Dead at " << deathTimeStamp << std::endl;
}

template<typename EntityType, typename StateType>
inline void DeadState<EntityType, StateType>::exit(EntityType* e)
{

}

template<typename EntityType, typename StateType>
inline bool DeadState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
{
	switch (msg.msg)
	{
	default:
		break;
	}
	return false;
}
