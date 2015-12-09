#pragma once

#include "GameEntity.h"
#include "Player.h"
#include "NPC.h"
#include "Utility.h"
#include <iostream>
#include <random>

#include <map>

class Player;

class Battle
{
private:
	std::map<int, Player*> players_;
	std::map<int, NPC*> mobs_;
	std::map<GameEntity*, GameEntity*> targets_;
	int id_;

	GameWorld& parent_;

	std::default_random_engine engine_;

public:
	Battle(int id, GameWorld* parent);
	~Battle();

	bool IsParticipant(GameEntity* p) const;

	NPC* GetMobByName(std::string name);
	Player* GetPlayerByName(std::string name);

	bool IsEmpty() const;

	void AddPlayer(GameEntity* p, GameEntity* target);
	void AddMob(GameEntity* p, GameEntity* target);
	void SetTarget(GameEntity* p, GameEntity* target);
	void PlayerFlee(GameEntity* p);
	void MobFlee(GameEntity* p);
	const int GetId() const;
	void Update();
	GameWorld& GetParent() const;
};