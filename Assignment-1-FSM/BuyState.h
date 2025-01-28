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
	const char* reasonLine = "";

	switch (e->getAgentStateMachine()->getPreviousState()->stateChangeReason)
	{
	case WORKING:

		break;
	case EATING:
		break;
	case DRINKING:
		break;
	case SLEEPING:
		reasonLine = "Enters the home to sleep";
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

	std::cout << Timer::instance().getTimeString() << e->getName() << ": " << reasonLine << std::endl;
}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::execute(EntityType* e)
{
}

template<typename EntityType, typename StateType>
inline void BuyState<EntityType, StateType>::exit(EntityType* e)
{
}
