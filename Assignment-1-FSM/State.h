#pragma once
//#include "BaseGameEntity.h"
//#include "Miner.h"

template <typename EntityType>
class State
{
public:
	virtual ~State() {};

	virtual void enter(EntityType* entity) = 0; 
	virtual void execute(EntityType* entity) = 0; 
	virtual void exit(EntityType* entity) = 0; 
};


//class State
//{
//public:
//	virtual ~State() {};
//
//	virtual void enter(BaseGameEntity* entity) = 0;
//	virtual void execute(BaseGameEntity* entity) = 0;
//	virtual void exit(BaseGameEntity* entity) = 0;
//};