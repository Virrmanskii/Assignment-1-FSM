#include "Agent.h"

//Miner::Miner() 
//{
//	this->id = this->NextValidID;
//	this->NextValidID += 1;
//}

Agent::Agent()
{

}

Agent::Agent(int id, Work job,std::string name)
{
	if (id >= this->NextValidID)
	{
		this->id = id;
		this->NextValidID = id + 1;
		this->name = name;
		this->work = job;
		//this->stateMachine = new StateMachine<Agent>(this);
		//this->stateMachine->setCurrentState(new EnterMineAndDigForGold<Agent>());
		this->agentStateMachine = new AgentStateMachine(this);
	}
	else
	{
		throw std::invalid_argument("recieved invalid BaseGameEntity ID");
	}
}

void Agent::update()
{
	//this->thirst += 1;
	//this->hunger += 1;
	double time = Timer::instance().getTime();
	if (this->cycleTimer <= time)
	{
		costOfExisting();
		this->cycleTimer = time + cycleCD;
	}
	
	this->agentStateMachine->update();
	//this->stateMachine->update();
	//if (currentState)
	//{
	//	currentState->execute(this);
	//}
}

void Agent::changeState(State2<Agent, AgentState>* newState)
{
	agentStateMachine->changeState(newState);
}

void Agent::setWork(Work newWork)
{
	this->work = newWork;
}

Work Agent::getWork()
{
	return this->work;
}

void Agent::setWorkCD(int CD)
{
	this->workCD = CD;
}

int Agent::getWorkCD()
{
	return this->workCD;
}

void Agent::setWorkTimer(double newTimer)
{
	this->workTimer = newTimer;
}

double Agent::getWorkTimer()
{
	return this->workTimer;
}

void Agent::setWalkCD(int CD)
{
	this->walkCD = CD;
}

int Agent::getWalkCD()
{
	return this->walkCD;
}

void Agent::setWalkTimer(double newTimer)
{
	this->walkTimer = newTimer;
}

double Agent::getWalkTimer()
{
	return this->walkTimer;
}

int Agent::getJobResource()
{
	return this->jobResource;
}

int Agent::getMoney()
{
	return this->money;
}

int Agent::getThirst()
{
	return this->thirst;
}

int Agent::getHunger()
{
	return this->hunger;
}

int Agent::getFatigue()
{
	return this->fatigue;
}

AgentStateMachine* Agent::getAgentStateMachine()
{
	return this->agentStateMachine;
}

void Agent::costOfExisting()
{
	increaseThirst(1);
	increaseHunger(1);
	increaseFatigue(1);
}

void Agent::increaseThirst(int increase)
{
	this->thirst += increase;
}

void Agent::decreaseThirst(int decrease)
{
	this->thirst -= decrease;
	if (this->thirst < 0)
	{
		this->thirst = 0;
	}
}

void Agent::increaseHunger(int increase)
{
	this->hunger += increase;
}

void Agent::decreaseHunger(int decrease)
{
	this->hunger -= decrease; 
	if (this->hunger < 0)
	{
		this->hunger = 0;
	}
}

void Agent::increaseFatigue(int increase)
{
	this->fatigue += increase;
}

void Agent::decreaseFatigue(int decrease)
{
	this->fatigue -= decrease;
	if (this->fatigue < 0)
	{
		this->fatigue = 0;
	}
}


//AgentStateMachine class defenitions
//-------------------------------------------------------------------------------------------------------------------


//AgentStateMachine::AgentStateMachine(Agent* owner)
//{
//	//this->setOwner(owner);
//}

void AgentStateMachine::setUp()
{
	this->states[AgentState::WORKING] = new WorkState<Agent, AgentState>();
	this->states[AgentState::WALKING] = new WalkState<Agent, AgentState>();

	this->setCurrentState(this->states.at(AgentState::WORKING));
}
