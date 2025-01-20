#include <iostream>
#include <chrono>
#include "Time.h"
#include "GameWorld.h"
#include "Miner.h"

void main()
{
	Miner bob(0);
	while (true)
	{
		Timer::instance().update();

		//do shit:
		GameWorld::instance().process(Timer::instance().getDeltaTime());
		bob.update();
		Timer::instance().stopDeltaTime();
	}
}