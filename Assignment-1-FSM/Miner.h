#pragma once
#include "BaseGameEntity.h"
//#include "State.h"
#include "Constants.h"
#include "EnterMineAndDigForGold.h"
class Miner : public BaseGameEntity
{
private:
	//EnterMineAndDigForGold<Miner> state1;
	State<Miner>* currentState = new EnterMineAndDigForGold<Miner>();
	//State* currentState = new EnterMineAndDigForGold();
	LocationType location;
	int goldCarried;
	int money;
	int thirst;
	int hunger;
	int fatigue;
	bool hasPickaxe;
	
	

public:
	//Miner() {};
	double miningCD = 0.0;
	Miner(int id, std::string name);
	
	void update();
	void changeState(State<Miner>* newState);
	//void changeState(State* newState);
};

