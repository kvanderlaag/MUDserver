#pragma once

#include "GameWorld.h"
#include "PlayerStats.h"

#include <map>
#include <vector>
#include <string>

class CharacterClass {
private:
	int id_;

	std::string name_;
	int health_;
	int mana_;
	int strength_;
	int dexterity_;
	int constitution_;
	int intelligence_;
	int charisma_;

	GameWorld & parent_;

public:
	CharacterClass(int id, std::string name, GameWorld* parent);
	CharacterClass(int id, std::string name, int health, int mana, int strength, int dexterity, int constitution, int intelligence, int charisma, GameWorld* parent);
	~CharacterClass();

	int GetId();
	GameWorld & GetParent();

	void SetName(std::string name);
	void SetHealth(int health);
	void SetMana(int mana);
	void SetStrength(int strength);
	void SetDexterity(int dexterity);
	void SetConstitution(int constitution);
	void SetIntelligence(int intelligence);
	void SetCharisma(int charisma);

	std::string GetName();
	int GetHealth();
	int GetMana();
	int GetStrength();
	int GetDexterity();
	int GetConstitution();
	int GetIntelligence();
	int GetCharisma();

	PlayerStats & GenerateStats(int level);
	void LevelUp(PlayerStats & stats);
};