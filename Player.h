#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameEntity.h"
#include <iostream>
#include <string>

class Player: public GameEntity{

private:
    int connectionID_;
	std::string name_;

public:
    Player( int id, std::string name);
	Player( int id, std::string name, int connectionID_);
    ~Player();
	void PrintPlayer();

	std::string GetName();
	int GetConnectionID();

};

#endif 
