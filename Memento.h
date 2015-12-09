#pragma once

#include "GameWorld.h"
#include "EntityList.h"
#include "CharacterClassList.h"
#include "FileParser.h"

#include <concurrent_vector.h>

class GameWorld;
class EntityList;
class CharacterClassList;
class FileParser;

class Memento
{
private:
	GameWorld & parent_;
	EntityList players_state_;

	const std::string players_file_ = "players.tsv";
	const std::string rooms_file_ = "rooms.tsv";
	const std::string items_file_ = "items.tsv";
	const std::string mobs_file_ = "npcs.tsv";
	const std::string character_classes_file_ = "characterclasses.tsv";

public:
	Memento(GameWorld & world);
	~Memento();

	void GetState();
	void SetState();

	void LoadPlayers();
	void LoadRooms();
	void LoadItems();
	void LoadMobs();
	void LoadCharacterClasses();

	void SavePlayers();

};
