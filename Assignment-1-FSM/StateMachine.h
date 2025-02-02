#pragma once
#include <map>
//#include "State.h"
#include "State2.0.h"

template <typename Entity_Type, typename Entity_State>
class StateMachine
{
public:
	std::map<Entity_State, State2<Entity_Type, Entity_State>*> states;

	StateMachine(Entity_Type* _owner);
	~StateMachine();

	void setCurrentState(State2<Entity_Type, Entity_State>* entity);
	void setGlobalState(State2<Entity_Type, Entity_State>* entity);
	void setPreviousState(State2<Entity_Type, Entity_State>* entity);
	State2<Entity_Type, Entity_State>* getCurrentState();
	State2<Entity_Type, Entity_State>* getGlobalState();
	State2<Entity_Type, Entity_State>* getPreviousState();
	void update() const;
	void changeState(State2<Entity_Type, Entity_State>* newState);
	void revertToPreviousState();
	void setOwner(Entity_Type* owner);
	bool handleMessage(const Telegram& msg) const;

protected:
	

	virtual void setUp() = 0;

private:
	Entity_Type* owner;
	State2<Entity_Type, Entity_State>* currentState = nullptr;
	State2<Entity_Type, Entity_State>* previousState = nullptr;
	State2<Entity_Type, Entity_State>* globalState = nullptr;
	
};
template <typename Entity_Type, typename Entity_State>
StateMachine<Entity_Type, Entity_State>::StateMachine(Entity_Type* owner)
{
	this->owner = owner;
	this->currentState = nullptr;
	this->previousState = nullptr;
	this->globalState = nullptr;
}

template <typename Entity_Type, typename Entity_State>
StateMachine<Entity_Type, Entity_State>::~StateMachine()
{
}

template<typename Entity_Type, typename Entity_State>
inline void StateMachine<Entity_Type, Entity_State>::setCurrentState(State2<Entity_Type, Entity_State>* entity)
{
	this->currentState = entity;
}

template<typename Entity_Type, typename Entity_State>
inline void StateMachine<Entity_Type, Entity_State>::setGlobalState(State2<Entity_Type, Entity_State>* entity)
{
	this->globalState = entity;
}

template<typename Entity_Type, typename Entity_State>
inline void StateMachine<Entity_Type, Entity_State>::setPreviousState(State2<Entity_Type, Entity_State>* entity)
{
	this->previousState = entity;
}

template<typename Entity_Type, typename Entity_State>
inline State2<Entity_Type, Entity_State>* StateMachine<Entity_Type, Entity_State>::getCurrentState()
{
	return this->currentState;
}

template<typename Entity_Type, typename Entity_State>
inline State2<Entity_Type, Entity_State>* StateMachine<Entity_Type, Entity_State>::getGlobalState()
{
	return this->globalState;
}

template<typename Entity_Type, typename Entity_State>
inline State2<Entity_Type, Entity_State>* StateMachine<Entity_Type, Entity_State>::getPreviousState()
{
	return this->previousState;
}

template<typename Entity_Type, typename Entity_State>
inline void StateMachine<Entity_Type, Entity_State>::update() const
{
	if (this->globalState != nullptr)
	{
		this->globalState->execute(this->owner);
	}

	if (this->currentState != nullptr)
	{
		this->currentState->execute(this->owner);
	}
}

template<typename Entity_Type, typename Entity_State>
inline void StateMachine<Entity_Type, Entity_State>::changeState(State2<Entity_Type, Entity_State>* newState)
{
	//TODO: make check for state change to null

	//Check for not switching to the same state.
	if (newState == this->currentState)
	{
		return;
	}

	this->previousState = this->currentState;
	this->currentState->exit(this->owner);
	this->currentState = newState;
	this->currentState->enter(this->owner);
}

template<typename Entity_Type, typename Entity_State>
inline void StateMachine<Entity_Type, Entity_State>::revertToPreviousState()
{
	changeState(this->previousState);
}

template<typename Entity_Type, typename Entity_State>
inline void StateMachine<Entity_Type, Entity_State>::setOwner(Entity_Type* owner)
{
	this->owner = owner;
}

template<typename Entity_Type, typename Entity_State>
inline bool StateMachine<Entity_Type, Entity_State>::handleMessage(const Telegram& msg) const
{
	if (this->currentState && this->currentState->onMessage(this->owner, msg))
	{
		return true;
	}
	return false;
}
