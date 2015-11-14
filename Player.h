#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameEntity.h"
#include "EntityList.h"
#include <iostream>
#include <string>

class Player: public GameEntity{
    
private:
    int* connectionID_;
    int password_;
    int* roomID_;
    EntityList* items_;
    
public:
    Player( int id, std::string name);
    Player( int id, std::string name, int password);
    ~Player();
    void PrintPlayer();
    
    void AssignConnectionID(int* newConnectionID);
    int* GetConnectionID();
    int* GetRoomID();
    bool CheckPassword(int inputPassword);
    void ChangeRoomID(int* newRoomID);
    void AddItem(GameEntity* entity);
	void RemoveItem(int id);
	GameEntity *GetItem(int id);
    
protected:
    int GetPassword();
};

#endif 
