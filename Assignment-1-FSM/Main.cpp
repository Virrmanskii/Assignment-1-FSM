#include <iostream>
#include <chrono>
#include "Time.h"
//#include "GameWorld.h"
#include "Agent.h"
#include "AgentManager.h"
#include "MessageDispatcher.h"

void main()
{
	Agent bob(0, WorkType::Miner,std::string("Bob"));
	Agent bobbelina(1, WorkType::Fisher, std::string("Bobbelina"));
	Agent bengan(2, WorkType::Fisher, std::string("Bengan"));

	//AgentManager entities;
	//entities.addEntity(&bob);
	AgentManager::instance()->addEntity(&bob);
	AgentManager::instance()->addEntity(&bobbelina);
	AgentManager::instance()->addEntity(&bengan);
	int cd = 1;
	double cycleTime = 0.0;

	while (true)
	{
		Timer::instance().update();
		//do shit:
		//GameWorld::instance().process(Timer::instance().getDeltaTime());

		AgentManager::instance()->update();
		MessageDispatcher::instance()->dispatchDelayedMessage();

		//bob.update();
		Timer::instance().stopDeltaTime();
	}
}