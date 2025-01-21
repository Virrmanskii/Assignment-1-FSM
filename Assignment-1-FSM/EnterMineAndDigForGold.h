#pragma once
#include <iostream>
//#include "Miner.h"
#include "State.h"
#include "Time.h"
//#include "BaseGameEntity.h"

template <typename Entity>
class EnterMineAndDigForGold : public State<Entity>    
{
public:
	//static EnterMineAndDigForGold* instance();
	void enter(Entity* e);
	void execute(Entity* e); 
	void exit(Entity* e); 
}; 

template <typename Entity>
inline void EnterMineAndDigForGold<Entity>::enter(Entity* e)
{
}

template <typename Entity>
void EnterMineAndDigForGold<Entity>::execute(Entity* e)
{
	double time = Timer::instance().getTime();
	if (e->miningCD <= time)
	{
		std::cout << Timer::instance().getTimeString() << e->getName() << ": " << "Digging" << std::endl;
		e->miningCD = time + 5;
	}

	//std::cout << "Digging" << std::endl;
	
}

template <typename Entity>
void EnterMineAndDigForGold<Entity>::exit(Entity* e)
{
}