#include <iostream>
#include <chrono>
#include "Time.h"
#include "GameWorld.h"
#include "Miner.h"

void main()
{
	
	while (true)
	{
		Timer::instance().update();

		//do shit:
		GameWorld::instance().process(Timer::instance().getDeltaTime());
		
		Timer::instance().stopDeltaTime();
	}
}