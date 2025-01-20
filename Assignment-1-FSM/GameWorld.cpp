#include "GameWorld.h"

GameWorld& GameWorld::instance()
{
	static GameWorld gameWorld;
	return gameWorld;
}

GameWorld::GameWorld()
{
	
}

//Updates every frame
void GameWorld::process(double delta)
{
	//Do game
}
