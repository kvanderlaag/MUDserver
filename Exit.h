#pragma once
#include "GameEntity.h"
class Exit :
	public GameEntity
{
private:
	std::string mDirection;
public:
	Exit(int id, std::string name, std::string direction);
	~Exit();
	std::string GetDirection() const;
	void SetDirection(std::string dir);
};

