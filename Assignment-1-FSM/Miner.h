#pragma once
#include "BaseGameEntity.h"
#include "State.h"
#include "Constants.h"
#include "EnterMineAndDigForGold.h"
class Miner : public BaseGameEntity
{
private:
	State<Miner>* currentState;
	LocationType location;
	int goldCarried;
	int money;
	int thirst;
	int hunger;
	int fatigue;
	bool hasPickaxe;
	

public:
	Miner() {};
	Miner(int id);
	
	void update();
	void changeState(State<Miner>* newState);
};

