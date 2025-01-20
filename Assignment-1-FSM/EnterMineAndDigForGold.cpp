#include "EnterMineAndDigForGold.h"
#include <iostream>

//EnterMineAndDigForGold* EnterMineAndDigForGold::instance()
//{
//	static EnterMineAndDigForGold instance;
//	return &instance;
//}

void EnterMineAndDigForGold::enter(Miner* miner)
{
}

void EnterMineAndDigForGold::execute(Miner* miner)
{
	std::cout << "Digging" << std::endl;
}

void EnterMineAndDigForGold::exit(Miner* miner)
{
}
