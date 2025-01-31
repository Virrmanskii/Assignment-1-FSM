#include <iostream>
#include <chrono>
#include "Time.h"
#include "GameWorld.h"
//#include "Agent.h"
#include "AgentManager.h"

void main()
{
	Agent bob(0, WorkType::Miner,std::string("Bob"));
	Agent bobbelina(1, WorkType::Fisher, std::string("Bobbelina"));

	//AgentManager entities;
	//entities.addEntity(&bob);
	AgentManager::instance()->addEntity(&bobbelina);


	while (true)
	{
		Timer::instance().update();
		//do shit:
		//GameWorld::instance().process(Timer::instance().getDeltaTime());

		AgentManager::instance()->update(); 

		//bob.update();
		Timer::instance().stopDeltaTime();
	}
}