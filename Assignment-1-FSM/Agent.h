#pragma once
#include "BaseGameEntity.h"
//#include "State.h"
#include "Constants.h"
#include "StateMachine.h"
//#include "AgentStateMachine.h"
#include "Workstate.h"
#include "WalkState.h"
#include "Work.h"
#include "EnterMineAndDigForGold.h"



class AgentStateMachine;

class Agent : public BaseGameEntity
{
private:
	//EnterMineAndDigForGold<Miner> state1;
	//State<Miner>* currentState = new EnterMineAndDigForGold<Miner>();
	//State* currentState = new EnterMineAndDigForGold();
	LocationType location;
	//StateMachine<Agent, AgentState>* stateMachine;
	AgentStateMachine* agentStateMachine;

	Work work;
	int jobResource;
	int money;
	int thirst;
	int hunger;
	int fatigue;
	bool workEquipment;
	double workTimer = 0;
	int workCD = 5;
	double walkTimer = 0;
	int walkCD = 3;
	double cycleTimer = 0;
	double cycleCD = 1;

	
	

public:
	Agent();
	~Agent() {};
	Agent(int id, Work job, std::string name);
	
	void update();
	void changeState(State2<Agent, AgentState>* newState);

	void setWork(Work newWork);
	Work getWork();

	void setWorkCD(int CD);
	int getWorkCD();

	void setWorkTimer(double newTimer);
	double getWorkTimer();

	void setWalkCD(int CD);
	int getWalkCD();

	void setWalkTimer(double newTimer);
	double getWalkTimer();

	int getJobResource();
	int getMoney();
	int getThirst();
	int getHunger();
	int getFatigue();
	AgentStateMachine* getAgentStateMachine();

	void costOfExisting();
	void increaseThirst(int increase);
	void decreaseThirst(int decrease);
	void increaseHunger(int increase);
	void decreaseHunger(int decrease);
	void increaseFatigue(int increase);
	void decreaseFatigue(int decrease);

	//void changeState(State* newState);
};


//TODO: fix this shit aka make AgentStateMachine a template class
class AgentStateMachine : public StateMachine<Agent, AgentState>
{
public:
	AgentStateMachine(Agent* owner) : StateMachine(owner) { this->setUp(); }
	~AgentStateMachine() {};

	void setUp() override;
};