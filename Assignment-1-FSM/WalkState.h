#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"

template <typename EntityType, typename StateType>
class WalkState : public State2<EntityType, StateType>
{
public:
	int walktick = 0;

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
	const char* reasonLine = "";

	switch (e->getAgentStateMachine()->getPreviousState()->stateChangeReason)
	{
	case WORKING:
		reasonLine = "to work ";
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
	default:
		break;
	}

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Starts walking " << reasonLine << std::endl;
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::execute(EntityType* e)
{
	double time = Timer::instance().getTime();

	//if (e->getFatigue() >= 50)
	//{
	//	this->stateChangeReason = SLEEPING;
	//	e->changeState(e->getAgentStateMachine()->states.at(WALKING));
	//}

	if (e->getWalkTimer() <= time)
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": Walking" << std::endl;
		e->setWalkTimer(time + e->getWalkCD());
		this->walktick += 1;
	}

	if (this->walktick == 3)
	{
		this->stateChangeReason = e->getAgentStateMachine()->getPreviousState()->stateChangeReason;
		e->changeState(e->getAgentStateMachine()->states.at(e->getAgentStateMachine()->getPreviousState()->stateChangeReason));
	}
}

template<typename EntityType, typename StateType>
inline void WalkState<EntityType, StateType>::exit(EntityType* e)
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
	default:
		break;
	}

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Stops walking" << std::endl;
	this->walktick = 0;
}
