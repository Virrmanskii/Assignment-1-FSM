#include "GameWorld.h"

GameWorld* GameWorld::s_ref = nullptr;

GameWorld& GameWorld::instance()
{
	static GameWorld gameWorld;
	return gameWorld;
}

GameWorld::GameWorld()
{
	std::cout << "world created";
	s_ref = this;
	//bob = Miner(0, std::string("Bob")); 
}

//Updates every frame
void GameWorld::process(double delta)
{
	//Do game
	while (true)
	{
		Timer::instance().update(); 
		//bob.update();
		Timer::instance().stopDeltaTime(); 
	} 
}
