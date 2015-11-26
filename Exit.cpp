#include "Exit.h"



Exit::Exit(int id, std::string name, std::string direction) : GameEntity(id, name),
	mDirection(direction)
{
}


Exit::~Exit()
{
}

std::string Exit::GetDirection() const {
	return mDirection;
}

void Exit::SetDirection(std::string dir){
	mDirection = dir;
}