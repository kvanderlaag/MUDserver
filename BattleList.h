#pragma once

#include "Battle.h"
#include "GameWorld.h"

#include <map>
#include <vector>
#include <string>

class Battle;
class GameWorld;

class BattleList
{
private:
	GameWorld& parent_;
	std::map<int, Battle*> battles_;
	std::vector<int> next_ids_;
public:
	BattleList(GameWorld* world);
	~BattleList();

	int GetNextId();
	void PutNextId(int nextId);

	void Update();

	void AddBattle(Battle* b);
	
	void DeleteBattle(Battle* b);
	void DeleteBattle(int id);

	Battle* GetBattleByPlayerName(std::string name);
	Battle* GetBattleByPlayerId(int id);

	Battle* GetBattleByMobName(std::string name);
	Battle* GetBattleByMobId(int id);

	GameWorld& GetParent() const;
};

