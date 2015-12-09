#pragma once

#include "CharacterClass.h"
#include "GameWorld.h"

#include <map>
#include <vector>
#include <string>

class CharacterClass;
class GameWorld;

class CharacterClassList
{
private:
	GameWorld& parent_;
	std::map<int, CharacterClass*> character_classes_;
	std::vector<int> next_ids_;
public:
	CharacterClassList(GameWorld* world);
	~CharacterClassList();

	int GetNextId();
	void PutNextId(int nextId);

	void AddCharacterClass(CharacterClass* c);

	void DeleteCharacterClass(CharacterClass* c);
	void DeleteCharacterClass(int id);

	CharacterClass* GetCharacterClassByName(std::string name);
	CharacterClass* GetCharacterClassById(int id);

	GameWorld& GetParent() const;
};