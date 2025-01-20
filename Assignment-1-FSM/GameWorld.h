#pragma once
#include <iostream>
#include "Miner.h"
class GameWorld
{
public:
	static GameWorld& instance();
	void process(double delta);

private:
	GameWorld(); 
};

