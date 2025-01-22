#pragma once
#include <iostream>
//#include "Miner.h"
#include "State.h"
#include "Time.h"
#include "Agent.h"
//#include "BaseGameEntity.h"

template <typename Entity>
class EnterMineAndDigForGold : public State<Entity>    
{
public:
	//static EnterMineAndDigForGold* instance();
	virtual void enter(Entity* e) override;
	virtual void execute(Entity* e) override;
	virtual void exit(Entity* e) override;
}; 

template <typename Entity>
inline void EnterMineAndDigForGold<Entity>::enter(Entity* e)
{
}

template <typename Entity>
void EnterMineAndDigForGold<Entity>::execute(Entity* e)
{
	double time = Timer::instance().getTime();
	if (e->getWorkTimer() <= time)
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": " << e->getWork().getActiveJobExecuteLine() << std::endl;
		e->setWorkTimer(time + e->getWorkCD());
		e->increaseFatigue(e->getWork().getJobIntensity());
		std::cout << e->getFatigue() << std::endl;
	}

	//std::cout << "Digging" << std::endl;
	
}

template <typename Entity>
void EnterMineAndDigForGold<Entity>::exit(Entity* e)
{
}