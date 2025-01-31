#pragma once
//#include <stdexcept>
#include <iostream>
#include "Telegram.h"

class BaseGameEntity
{
protected:
	int id;
	static int NextValidID;
	std::string name;

	void setID(int id);

public:
	BaseGameEntity() {};
	BaseGameEntity(int id);
	~BaseGameEntity() {};

	virtual void update() = 0;
	virtual bool handleMessage(const Telegram& msg) = 0;
	int ID()const { return id; };
	void setName(std::string);
	std::string getName();
};

