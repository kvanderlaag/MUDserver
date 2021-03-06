#pragma once
#include "GameEntity.h"
#include "GameWorld.h"
#include "PlayerStats.h"
#include "EntityList.h"
#include "Battle.h"

#include <string>
#include <memory>

class Battle;
class GameWorld;

class NPC :
	public GameEntity
{
private:
	std::unique_ptr<PlayerStats> stats_;
	std::unique_ptr<EntityList> items_;
	int master_id_;
	int room_id_;
public:
	NPC(int id, std::string name, GameWorld* world, int master);
	NPC(int newId, const NPC& other);
	~NPC();

	int Damage(const int damage);
	void Die();

	PlayerStats& GetStats() const;
	EntityList& GetItems() const;
	
	int GetRoomId() const;
	void SetRoomId(int roomId);

	int GetMasterId() const;


};

