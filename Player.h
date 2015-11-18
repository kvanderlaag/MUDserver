/**
* Header file Player is an entity inherent object GameEntity.
* Player also includes an entity list for the item inventory.
*/
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameEntity.h"
#include "EntityList.h"
#include <iostream>
#include <string>

/**
* Player extents GameEntity's functionailty by adding connection ID, password, room ID, and an entity list for storing items.
*/
class Player: public GameEntity{

/**
* The private variable connectionID_ is a pointer variable and is assigned by the server by passing a temporary integer. It points to the assigned integer.
* The private variable password_ is filled in when object Player is created by constructor, which cannot be modify until object Player is being removed
* The private variable roomID_ is a pointer variable points to a room ID passed by the server when the room where the player located at has changed.
* The roomID_ shows the current room for the player.
* The private variable items_ is a entity list pointer points to a list of items. Player can add, remove, and find the items within the object.
*/    
private:
    int* connectionID_;
    int password_;
    int* roomID_;
    EntityList* items_;

/**
 *Public functions have default constructor, a standard constructor, a destrutor, and a print out function.
 *Other public functions for more functionailties for player object have get/assign connection ID, verify password, get/modify room ID where the player located,
 *add/remove/find a item with an item list within player object.
 */
public:
    Player( int id, std::string name);
    Player( int id, std::string name, int password);
    ~Player();
    void PrintPlayer();
    
    void AssignConnectionID(int* newConnectionID);
    int* GetConnectionID();
    int* GetRoomID();
    void ChangeRoomID(int* newRoomID);
    void AddItem(GameEntity* entity);
	void RemoveItem(int id);
	GameEntity *GetItem(int id);

/*The function GetPassword returns the initial password of the player.*/  
    int GetPassword();
};

#endif 
