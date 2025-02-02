#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"
#include "Constants.h"
#include "MessageDispatcher.h"
#include "AgentManager.h"

template <typename EntityType, typename StateType>
class SocializeState : public State2<EntityType, StateType>
{
private:
	int sTickCounter = 0;
public:
	SocializeState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline SocializeState<EntityType, StateType>::SocializeState()
{
}

template<typename EntityType, typename StateType>
inline void SocializeState<EntityType, StateType>::enter(EntityType* e)
{
	e->setLocation(LocationType::ACTIVITY_CENTER);

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
	case DEAD:
		break;
	default:
		break;
	}
	std::cout << Timer::instance().getTimeString() << e->getName() << ": +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
}

template<typename EntityType, typename StateType>
inline void SocializeState<EntityType, StateType>::execute(EntityType* e)
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

	std::cout << Timer::instance().getTimeString() << e->getName() << ": Socializing" << std::endl;
	
}

template<typename EntityType, typename StateType>
inline void SocializeState<EntityType, StateType>::exit(EntityType* e)
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
	case DEAD:
		break;
	default:
		break;
	}
}

template<typename EntityType, typename StateType>
inline bool SocializeState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
{
	switch (msg.msg)
	{
	default:
		break;
	}
	return false;
}
