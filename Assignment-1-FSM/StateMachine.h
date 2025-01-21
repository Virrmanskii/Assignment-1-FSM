#pragma once
#include "State.h"

template <class Entity_Type>
class StateMachine
{
public:
	StateMachine(Entity_Type* owner);
	~StateMachine();

	void setCurrentState(State<Entity_Type>* entity);
	void setGlobalState(State<Entity_Type>* entity);
	void setPreviousState(State<Entity_Type >* entity);
	State<Entity_Type>* getCurrentState();
	State<Entity_Type>* getGlobalState();
	State<Entity_Type>* getPreviousState();
	void update() const;
	void changeState(State<Entity_Type>* newState);
	void revertToPreviousState();


private:
	Entity_Type* owner;
	State<Entity_Type>* currentState;
	State<Entity_Type>* previousState;
	State<Entity_Type>* globalState;


};
template <class Entity_Type>
StateMachine<Entity_Type>::StateMachine(Entity_Type* owner)
{
	this->currentState = nullptr;
	previousState = nullptr;
	globalState = nullptr;
}

template <class Entity_Type>
StateMachine<Entity_Type>::~StateMachine()
{
}

template<class Entity_Type>
inline void StateMachine<Entity_Type>::setCurrentState(State<Entity_Type>* entity)
{
	this->currentState = entity
}

template<class Entity_Type>
inline void StateMachine<Entity_Type>::setGlobalState(State<Entity_Type>* entity)
{
	this->globalState = entity
}

template<class Entity_Type>
inline void StateMachine<Entity_Type>::setPreviousState(State<Entity_Type>* entity)
{
	this->previousState = entity
}

template<class Entity_Type>
inline State<Entity_Type>* StateMachine<Entity_Type>::getCurrentState()
{
	return this->currentState;
}

template<class Entity_Type>
inline State<Entity_Type>* StateMachine<Entity_Type>::getGlobalState()
{
	return this->globalState;
}

template<class Entity_Type>
inline State<Entity_Type>* StateMachine<Entity_Type>::getPreviousState()
{
	return this->previousState;
}

template<class Entity_Type>
inline void StateMachine<Entity_Type>::update() const
{
	if (this->globalState)
	{
		this->globalState->execute();
	}

	if (this->currentState)
	{
		this->currentState->execute();
	}
}

template<class Entity_Type>
inline void StateMachine<Entity_Type>::changeState(State<Entity_Type>* newState)
{
	//TODO: make check for state change to null
	this->previousState = this->currentState;
	this->currentState->exit();
	this->currentState = newState;
	this->currentState->enter();
}

template<class Entity_Type>
inline void StateMachine<Entity_Type>::revertToPreviousState()
{
	changeState(this->previousState)
}
