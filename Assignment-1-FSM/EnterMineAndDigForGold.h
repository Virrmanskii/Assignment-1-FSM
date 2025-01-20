#pragma once
#include "Miner.h"
#include "State.h"


class EnterMineAndDigForGold : public State<Miner>
{
public:
	//static EnterMineAndDigForGold* instance();
	void enter(Miner* miner); 
	void execute(Miner* miner); 
	void exit(Miner* miner); 
};

