#pragma once
#include "Telegram.h"

template <typename EntityType, typename StateType>
class State2
{
public:
	StateType stateChangeReason;
	//State2(StateType _key) : key(_key){}
	virtual ~State2() {};

	virtual void enter(EntityType* entity) = 0;
	virtual void execute(EntityType* entity) = 0;
	virtual void exit(EntityType* entity) = 0;
	virtual bool onMessage(EntityType* entity, const Telegram&) = 0;
};