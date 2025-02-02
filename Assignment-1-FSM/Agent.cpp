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
		this->agentStateMachine->update();
	}
	//costOfExisting();
	//this->agentStateMachine->update();
	
	//this->stateMachine->update();
	//if (currentState)
	//{
	//	currentState->execute(this);
	//}
}

bool Agent::handleMessage(const Telegram& msg)
{
	return this->agentStateMachine->handleMessage(msg);
}

void Agent::changeState(State2<Agent, AgentState>* newState)
{
	agentStateMachine->changeState(newState);
}

LocationType Agent::getLocation()
{
	return this->location;
}

void Agent::setLocation(LocationType newLocation)
{
	this->location = newLocation;
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

void Agent::setSleepCD(int CD)
{
	this->sleepCD = CD;
}

int Agent::getSleepCD()
{
	return this->sleepCD;
}

void Agent::setSleepTimer(double newTimer)
{
	this->sleepTimer = newTimer;
}

double Agent::getSleepTimer()
{
	return this->sleepTimer;
}

void Agent::setEatCD(int CD)
{
	this->eatCD = CD;
}

int Agent::getEatCD()
{
	return this->eatCD;
}

void Agent::setEatTimer(double newTimer)
{
	this->eatTimer = newTimer;
}

double Agent::getEatTimer()
{
	return this->eatTimer;
}

void Agent::setDrinkCD(int CD)
{
	this->drinkCD = CD;
}

int Agent::getDrinkCD()
{
	return this->drinkCD;
}

void Agent::setDrinkTimer(double newTimer)
{
	this->drinkTimer = newTimer;
}

double Agent::getDrinkTimer()
{
	return this->drinkTimer;
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

int Agent::getWater()
{
	return this->water;
}

void Agent::setWater(int newAmount)
{
	this->water += newAmount;
}

int Agent::getHunger()
{
	return this->hunger;
}

int Agent::getFood()
{
	return this->food;
}

void Agent::setFood(int newAmount)
{
	this->food += newAmount;
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

void Agent::increaseJobResource(int increase)
{
	this->jobResource += increase;
}

void Agent::decreaseJobResource(int decrease)
{
	this->jobResource -= decrease;
	if (this->jobResource < 0)
	{
		this->jobResource = 0;
	}
}

void Agent::increaseMoney(int increase)
{
	this->money += increase;
}

void Agent::decreaseMoney(int decrease)
{
	this->money -= decrease;
	if (this->money < 0)
	{
		this->money = 0;
	}
}

bool Agent::isHungry()
{
	if (this->hunger >= 50)
	{
		return true;
	}
	return false;
}

bool Agent::isThirsty()
{
	if (this->thirst >= 50)
	{
		return true;
	}
	return false;
}

bool Agent::isFatigued()
{
	if (this->fatigue >= 150)
	{
		return true;
	}
	return false;
}

bool Agent::hasMoney()
{
	if (this->money >= 60)
	{
		return true;
	}
	return false;
}

bool Agent::isDead()
{
	if (this->fatigue >= 200 || this->thirst >= 100|| this->hunger >= 100)
	{
		return true;
	}
	return false;
}

bool Agent::canSocialize()
{
	if (!isHungry() && this->fatigue < 80 && !isThirsty())
	{
		return true;
	}
	return false;
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
	this->states[AgentState::SLEEPING] = new SleepingState<Agent, AgentState>();
	this->states[AgentState::EATING] = new EatState<Agent, AgentState>(); 
	this->states[AgentState::DRINKING] = new DrinkState<Agent, AgentState>();
	this->states[AgentState::BUYING] = new BuyState<Agent, AgentState>();
	this->states[AgentState::DEAD] = new DeadState<Agent, AgentState>();
	this->states[AgentState::SOCIALIZE] = new SocializeState<Agent, AgentState>();

	this->setCurrentState(this->states.at(AgentState::WORKING));
}
