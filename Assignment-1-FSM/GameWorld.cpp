#include "GameWorld.h"

GameWorld& GameWorld::instance()
{
	static GameWorld gameWorld;
	return gameWorld;
}

GameWorld::GameWorld()
{
	bob = Miner(0, std::string("Bob")); 
}

//Updates every frame
void GameWorld::process(double delta)
{
	//Do game
	while (true)
	{
		Timer::instance().update(); 
		bob.update();
		Timer::instance().stopDeltaTime(); 
	} 
}
