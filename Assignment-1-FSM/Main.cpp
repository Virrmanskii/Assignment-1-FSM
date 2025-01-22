#include <iostream>
#include <chrono>
#include "Time.h"
#include "GameWorld.h"
#include "Agent.h"

void main()
{
	Agent bob(0, WorkType::Miner,std::string("Bob"));
	while (true)
	{
		Timer::instance().update();

		//do shit:
		//GameWorld::instance().process(Timer::instance().getDeltaTime());
		bob.update();
		
		Timer::instance().stopDeltaTime();
	}
}