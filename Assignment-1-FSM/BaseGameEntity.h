#pragma once
#include <stdexcept>
class BaseGameEntity
{
protected:
	int id;
	static int NextValidID;

	void setID(int id);

public:
	BaseGameEntity() {};
	BaseGameEntity(int id);
	~BaseGameEntity() {};

	virtual void update() = 0;
	int ID()const { return id; };
};

