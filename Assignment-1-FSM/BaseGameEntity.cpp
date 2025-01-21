#include "BaseGameEntity.h"

int BaseGameEntity::NextValidID = 0;

void BaseGameEntity::setID(int id)
{
	//if (id >= this->NextValidID)
	//{
	//	this->id = id;
	//	this->NextValidID = id + 1;
	//}
	//else
	//{
	//	throw std::invalid_argument("recieved invalid BaseGameEntity ID");
	//}
}

BaseGameEntity::BaseGameEntity(int id)
{
	setID(id);
}

void BaseGameEntity::setName(std::string name)
{
	this->name = name;
}

std::string BaseGameEntity::getName()
{
	return this->name;
}
