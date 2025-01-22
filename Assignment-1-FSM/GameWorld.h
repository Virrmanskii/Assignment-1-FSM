#pragma once
#include <iostream>
#include "Time.h"
#include "Agent.h"
class GameWorld
{
public:
	static GameWorld& instance();
	void process(double delta);
	//Miner bob;

private:
	GameWorld();
	static GameWorld* s_ref;
};

