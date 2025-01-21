#pragma once
#include <iostream>
#include "Time.h"
#include "Miner.h"
class GameWorld
{
public:
	static GameWorld& instance();
	void process(double delta);
	Miner bob;

private:
	GameWorld(); 
};

