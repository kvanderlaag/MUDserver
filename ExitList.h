#pragma once
#include "EntityList.h"
#include "Exit.h"
class ExitList :
	public EntityList
{
private:
	std::map<int, Exit*> map_;
public:
	ExitList();
	~ExitList();
};

