#pragma once
#include "vector"
#include "map"
//#include "Agent.h"
#include "BaseGameEntity.h"

class AgentManager
{
private:
	AgentManager() {};
public:
	std::map<int, BaseGameEntity*> agents;

	~AgentManager();

	static AgentManager* instance();
	void addEntity(BaseGameEntity*);
	void removeEntity(BaseGameEntity*);
	BaseGameEntity* getEntityFromID(int id);
	void update();
};

