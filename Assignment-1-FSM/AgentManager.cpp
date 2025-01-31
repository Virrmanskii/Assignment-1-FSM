#include "AgentManager.h"

AgentManager::~AgentManager()
{
}

AgentManager* AgentManager::instance()
{
	static AgentManager manager;
	return &manager;
}

void AgentManager::addEntity(BaseGameEntity* newAgent)
{
	//this->agents.push_back(newAgent);
	for (auto i : this->agents)
	{
		if (i.first == newAgent->ID())
		{
			//found dup
			return;
		}
	}
	this->agents[newAgent->ID()] = newAgent;
}

void AgentManager::removeEntity(BaseGameEntity* agentToDelete)
{

}

BaseGameEntity* AgentManager::getEntityFromID(int id)
{
	return this->agents.at(id);
}

void AgentManager::update()
{
	for (auto i : this->agents)
	{
		i.second->update();
	}

	//for (int i = 0; i < this->agents.size(); i++)
	//{
	//	agents.at(i)->update();
	//}
}
