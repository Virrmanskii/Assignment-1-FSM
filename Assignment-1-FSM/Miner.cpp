#include "Miner.h"

//Miner::Miner() 
//{
//	this->id = this->NextValidID;
//	this->NextValidID += 1;
//}

Miner::Miner(int id, std::string name)
{
	if (id >= this->NextValidID)
	{
		this->id = id;
		this->NextValidID = id + 1;
		this->name = name;
	}
	else
	{
		throw std::invalid_argument("recieved invalid BaseGameEntity ID");
	}
}

void Miner::update()
{
	this->thirst += 1;
	this->hunger += 1;

	if (currentState)
	{
		currentState->execute(this);
	}
}
