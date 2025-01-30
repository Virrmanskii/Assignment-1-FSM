#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"
#include "Constants.h"

//#include "Agent.h"
//class Agent;
//enum AgentState;
//
//class WorkState : public State2<Agent, AgentState>
//{
//public:
//	WorkState(AgentState state) : State2(state) {}
//
//	void enter(Agent* e) override;
//	void execute(Agent* e) override;
//	void exit(Agent* e) override;
//};

template <typename EntityType, typename StateType> 
class WorkState : public State2<EntityType, StateType>
{
public:
	//WorkState(AgentState state) : State2(state) {}
	//AgentState stateChangeReason;
	WorkState();

	void enter(EntityType* e) override;
	void execute(EntityType* e) override;
	void exit(EntityType* e) override;
};

template<typename EntityType, typename StateType>
inline WorkState<EntityType, StateType>::WorkState()
{
}

template<typename EntityType, typename StateType>
inline void WorkState<EntityType, StateType>::enter(EntityType* e)
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
}

template<typename EntityType, typename StateType>
inline void WorkState<EntityType, StateType>::execute(EntityType* e)
{
	double time = Timer::instance().getTime();


	std::cout << Timer::instance().getTimeString() << e->getName() << ": " << e->getWork().getActiveJobExecuteLine() << std::endl;
	e->increaseFatigue(e->getWork().getJobIntensity());
	e->increaseJobResource(e->getWork().getActiveJobResourceAmount());

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

	//if (e->getWorkTimer() <= time)
	//{
	//	std::cout << Timer::instance().getTimeString() << e->getName() << ": " << e->getWork().getActiveJobExecuteLine() << std::endl;
	//	e->setWorkTimer(time + e->getWorkCD());
	//	e->increaseFatigue(e->getWork().getJobIntensity());
	//	e->increaseJobResource(e->getWork().getActiveJobResourceAmount());
	//}
}

template<typename EntityType, typename StateType>
inline void WorkState<EntityType, StateType>::exit(EntityType* e)
{
	const char* reasonLine = "";
	
	switch (this->stateChangeReason)
	{
	case WORKING:
		break;
	case EATING:
		reasonLine = " because he's hungry.";
		break;
	case DRINKING:
		reasonLine = " because he's thirsty.";
		break;
	case SLEEPING:
		reasonLine = " because he's tired.";
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

	std::cout << Timer::instance().getTimeString() << e->getName() << ": " << e->getWork().getActiveJobExitLine() << reasonLine << std::endl;
}
