#pragma once
#include "BaseGameEntity.h"

template <class EntityType>
class State
{
public:
	virtual ~State() {};

	virtual void enter(EntityType* entity) = 0; 
	virtual void execute(EntityType* entity) = 0; 
	virtual void exit(EntityType* entity) = 0; 
};