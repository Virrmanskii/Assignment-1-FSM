#include "BaseGameEntity.h"

int BaseGameEntity::NextValidID = 0;

void BaseGameEntity::setID(int id)
{

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
