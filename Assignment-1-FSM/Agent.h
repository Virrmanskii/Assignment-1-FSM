#pragma once
#include "BaseGameEntity.h"
//#include "State.h"
#include "Constants.h"
#include "StateMachine.h"
#include "Workstate.h"
#include "WalkState.h"
#include "SleepingState.h"
#include "EatState.h"
#include "DrinkState.h"
#include "BuyState.h"
#include "DeadState.h"
#include "SocializeState.h"

#include "Work.h"
#include "EnterMineAndDigForGold.h"



class AgentStateMachine;

class Agent : public BaseGameEntity
{
private:
	LocationType location;
	AgentStateMachine* agentStateMachine;

	Work work;
	int jobResource;
	int money;
	int thirst;
	int water = 2;
	int hunger;
	int food = 3;
	int fatigue;

	double cycleTimer = 0;
	double cycleCD = 1;


public:
	//bool response = false;

	Agent();
	~Agent() {};
	Agent(int id, Work job, std::string name);
	
	void update();
	bool handleMessage(const Telegram& meg) override;
	void changeState(State2<Agent, AgentState>* newState);
	LocationType getLocation();
	void setLocation(LocationType newLocation);

	void setWork(Work newWork);
	Work getWork();

	int getJobResource();
	int getMoney();
	int getThirst();
	int getWater();
	void setWater(int newAmount);
	int getHunger();
	int getFood();
	void setFood(int newAmount);
	int getFatigue();
	AgentStateMachine* getAgentStateMachine();

	void costOfExisting();
	void increaseThirst(int increase);
	void decreaseThirst(int decrease);
	void increaseHunger(int increase);
	void decreaseHunger(int decrease);
	void increaseFatigue(int increase);
	void decreaseFatigue(int decrease);
	void increaseJobResource(int increase);
	void decreaseJobResource(int decrease);
	void increaseMoney(int increase);
	void decreaseMoney(int decrease);

	bool isHungry();
	bool isThirsty();
	bool isFatigued();
	bool hasMoney();
	bool isDead();
	bool canSocialize();
};


//TODO: fix this shit aka make AgentStateMachine a template class
class AgentStateMachine : public StateMachine<Agent, AgentState>
{
public:
	AgentStateMachine(Agent* owner) : StateMachine(owner) { this->setUp(); }
	~AgentStateMachine() {};

	void setUp() override;
};