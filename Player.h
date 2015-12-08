/**
* Header file Player.h inherits GameEntity.
* Player also includes an entity list for the item inventory.
*/
#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameEntity.h"
#include "GameWorld.h"
#include "EntityList.h"
#include "PlayerStats.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cctype>


/**
* Player extends GameEntity's functionailty by adding connection ID, password, room ID, and an entity list for storing items.
*/
class Player: public GameEntity
{

/**
* The private variable connectionID_ is a pointer variable and is assigned by the server by passing a temporary integer. It points to the assigned integer.
* The private variable password_ is filled in when object Player is created by constructor, which cannot be modify until object Player is being removed
* The private variable roomID_ is a pointer variable points to a room ID passed by the server when the room where the player located at has changed.
* The roomID_ shows the current room for the player.
* The private variable items_ is a entity list pointer points to a list of items. Player can add, remove, and find the items within the object.
*/
private:
	int connection_id_;
	std::string password_;

	int room_id_;
	std::unique_ptr<EntityList> items_;

	std::unique_ptr<PlayerStats> stats_;

/**
 *Public functions have default constructor, a standard constructor, a destrutor, and a print out function.
 *Other public functions for more functionailties for player object have get/assign connection ID, verify password, get/modify room ID where the player located,
 *add/remove/find a item with an item list within player object.
 */
public:

	Player(int id, std::string name, GameWorld* world);
	Player(int id, std::string name, std::string password, GameWorld* world);
	~Player();
	void PrintPlayer();

	void SetConnectionId(int connection_id);
	int GetConnectionId();

	void SetRoomId(int room_id);
	int GetRoomId();

	void AddItem(GameEntity& entity);
	void RemoveItem(int id);
	void RemoveItem(std::string name);
	GameEntity* GetItem(int id);
	std::vector<GameEntity*> GetItemVector();
	GameEntity* FindItem(std::string name) const;
	
	int Damage(const int damage);

	PlayerStats& GetStats();

	/**The function GetPassword returns the initial password of the player.*/  
	std::string GetPassword() const;
	void SetPassword(std::string password);
};

#endif
