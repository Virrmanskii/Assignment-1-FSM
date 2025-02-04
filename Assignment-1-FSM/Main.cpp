#include <iostream>
#include <chrono>
#include "Time.h"
#include "Agent.h"
#include "AgentManager.h"
#include "MessageDispatcher.h"

void main()
{
	Agent bob(0, WorkType::Miner,std::string("Bob"));
	Agent bobbelina(1, WorkType::Fisher, std::string("Bobbelina"));
	Agent bengan(2, WorkType::Fisher, std::string("Bengan"));
	Agent babben(3, WorkType::Miner, std::string("Babben"));

	AgentManager::instance()->addEntity(&bob);
	AgentManager::instance()->addEntity(&bobbelina);
	AgentManager::instance()->addEntity(&bengan);
	AgentManager::instance()->addEntity(&babben);
	int cd = 1;
	double cycleTime = 0.0;

	while (true)
	{
		Timer::instance().update();


		AgentManager::instance()->update();
		MessageDispatcher::instance()->dispatchDelayedMessage();

		Timer::instance().stopDeltaTime();
	}
}