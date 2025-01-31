#pragma once
#include "vector"
#include "map"
#include "Agent.h"

class AgentManager
{
private:
	AgentManager() {};
public:
	std::map<int, Agent*> agents;

	~AgentManager();

	static AgentManager* instance();
	void addEntity(Agent*);
	void removeEntity(Agent*);
	Agent* getEntityFromID(int id);
	void update();
};

