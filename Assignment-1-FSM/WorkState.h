#pragma once
#include "State2.0.h"
#include <iostream>
#include "Time.h"
#include "Constants.h"
#include "MessageDispatcher.h"
#include "AgentManager.h"

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
	bool onMessage(EntityType* entity, const Telegram& msg) override;
};

template<typename EntityType, typename StateType>
inline WorkState<EntityType, StateType>::WorkState()
{
}

template<typename EntityType, typename StateType>
inline void WorkState<EntityType, StateType>::enter(EntityType* e)
{
	e->setLocation(e->getWork().getWorkLocation());

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
	
	// 2% propability to trigger meetup message
	bool trueFalse = (rand() % 100) < 20;
	if (trueFalse)
	{
		if (e->canSocialize())
		{
			for (auto agent : AgentManager::instance()->agents)
			{
				if (e->ID() != agent.first)
				{
					std::cout << Timer::instance().getTimeString() << e->getName() << ": sent message to " << agent.second->getName() << " to hang out at "<< Timer::instance().getTimeString(time + 20.0) << "\n";
					MessageDispatcher::instance()->dispatchMessage(0.0, e->ID(), agent.first, Message::WANT_TO_SOCIALIZE, 20.0);
				}
			}
		}
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

template<typename EntityType, typename StateType>
inline bool WorkState<EntityType, StateType>::onMessage(EntityType* entity, const Telegram& msg)
{
	switch (msg.msg)
	{
	case Message::TIME_TO_SOCIALIZE:
		
		if (entity->canSocialize())
		{
			//entity->getAgentStateMachine()->getCurrentState()->stateChangeReason = AgentState::SOCIALIZE;
			//entity->changeState(entity->getAgentStateMachine()->states.at(WALKING));
			MessageDispatcher::instance()->dispatchMessage(0.0, entity->ID(), entity->ID(), Message::CAN_SOCIALIZE, 0.0);
		}
		else
		{
			std::cout << Timer::instance().getTimeString() << entity->getName() << ": Aww i can't come\n";
		}
		
		return true;
		break;

	case Message::CAN_SOCIALIZE:
		std::cout << Timer::instance().getTimeString() << entity->getName() << ": Oh right, time to hang out\n";
		entity->getAgentStateMachine()->getCurrentState()->stateChangeReason = AgentState::SOCIALIZE;
		entity->changeState(entity->getAgentStateMachine()->states.at(WALKING));

		return true;
		break;
	case Message::WANT_TO_SOCIALIZE:
		std::cout << Timer::instance().getTimeString() << entity->getName() << ": Of course i want to hang out at " << Timer::instance().getTimeString(msg.timeDisplacement) << "\n";
		MessageDispatcher::instance()->dispatchMessage(msg.timeDisplacement, entity->ID(), entity->ID(), Message::TIME_TO_SOCIALIZE, 0.0);
		MessageDispatcher::instance()->dispatchMessage(msg.timeDisplacement, entity->ID(), msg.sender, Message::TIME_TO_SOCIALIZE, 0.0);
		return true;
		break;

	default:
		break;
	}
	return false;
}
