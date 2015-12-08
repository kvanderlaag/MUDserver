#include "Memento.h"

Memento::Memento(GameWorld & world) :
	parent_(world)
{
}

Memento::~Memento()
{
}

void Memento::GetState()
{
	LoadItems();
	LoadMobs();
	LoadRooms();
	LoadPlayers();
	LoadCharacterClasses();

}

void Memento::SetState()
{
	SavePlayers();

}

/**
* Load Players from file
*/
void Memento::LoadPlayers() {
	std::vector<std::string>* players = FileParser::ParseFile(players_file_);
#ifdef _DEBUG_FLAG
	std::cout << "Loading players..." << std::endl;
#endif
	for (size_t i = 0; i < players->size(); ++i) {
		std::vector<std::string>* player_values = FileParser::ParseTsv(players->at(i));
		std::string name = player_values->at(0);
		std::string password = player_values->at(1);

		Player* player = new Player(parent_.GetPlayers().GetNextId(), name, password, &parent_);

		if (player_values->size() > 2) {
			std::stringstream s_current_room(player_values->at(2));

			int current_room;

			if (s_current_room >> current_room) {
				player->SetRoomId(current_room);
			}
		}


		if (player_values->size() > 3) {
			std::vector<std::string>* player_stats = FileParser::ParseCsv(player_values->at(3));

			if (player_stats->size() >= 7) {
				int health, mana, strength, dexterity, constitution, intelligence, charisma;
				std::stringstream sHealth(player_stats->at(0));
				std::stringstream sMana(player_stats->at(1));
				std::stringstream sStr(player_stats->at(2));
				std::stringstream sDex(player_stats->at(3));
				std::stringstream sCon(player_stats->at(4));
				std::stringstream sInt(player_stats->at(5));
				std::stringstream sCha(player_stats->at(6));

				sHealth >> health;
				sMana >> mana;
				sStr >> strength;
				sDex >> dexterity;
				sCon >> constitution;
				sInt >> intelligence;
				sCha >> charisma;

				player->GetStats().SetStats(health, mana, strength, dexterity, constitution, intelligence, charisma);
			}
		}

		if (player_values->size() > 4) {
			player->SetDescription(player_values->at(4));
		}

		if (player_values->size() > 5) {
			std::vector<std::string>* playerInventory = FileParser::ParseCsv(player_values->at(5));
			for (std::string sItemId : *playerInventory) {
				std::stringstream sId(sItemId);
				int itemId;
				if (sId >> itemId) {
					Item* i = new Item(parent_.GetItems().GetNextId(), (Item&)*(parent_.GetMasterItems().GetEntity(itemId)));
					parent_.GetItems().AddEntity(*i);
					player->AddItem(*i);
				}
			}
		}
		// add to player list
		parent_.GetPlayers().AddEntity(*player);
	}
}

/**
* Load rooms from file
*/
void Memento::LoadRooms() {
	std::vector<std::string>* rooms = FileParser::ParseFile(rooms_file_);

#ifdef _DEBUG_FLAG
	std::cout << "Loading Rooms...";
#endif
	for (size_t i = 0; i != rooms->size(); i++) {

		std::vector<std::string>* room_values = FileParser::ParseTsv(rooms->at(i));
		std::string name = room_values->at(0);
		std::string description = room_values->at(1);
		Room* room = new Room(parent_.GetRooms().GetNextId(), name, description, &parent_);

		if (room_values->size() > 4) {
			std::vector<std::string>* items = FileParser::ParseCsv(room_values->at(4));
			if (items) {
				for (std::string item_id : *items) {
					std::stringstream buffer(item_id);
					int intId;
					if (buffer >> intId) {
						if (parent_.GetMasterItems().GetEntity(intId)) {
							Item* item = new Item(parent_.GetItems().GetNextId(), (Item&)*(parent_.GetMasterItems().GetEntity(intId)));
							room->AddItem(*item);
							room->AddMasterItem(intId);
						}
					}

				}
			}
		}

		if (room_values->size() > 5) {
			//std::cout << "Loading mobs.\n" << std::endl;
			std::vector<std::string>* mobs = FileParser::ParseCsv(room_values->at(5));
			if (mobs) {
				for (std::string mob_id : *mobs) {
					std::stringstream buffer(mob_id);
					int intId;
					if (buffer >> intId) {
						if (parent_.GetMasterMobs().GetEntity(intId)) {
							NPC* mob = new NPC(parent_.GetMobs().GetNextId(), (NPC&)*(parent_.GetMasterMobs().GetEntity(intId)));
							//std::cout << "Adding mob " << mob->GetName() << " to " << room->GetName() << "\n";
							room->AddMob(*mob);
							room->AddMasterMob(intId);
						}
					}

				}
			}
		}

		parent_.GetRooms().AddEntity(*room);
	}
#ifdef _DEBUG_FLAG
	std::cout << "Loading Exits...";
#endif
	for (size_t i = 0; i != rooms->size(); i++) {

		std::vector<std::string>* room_values = FileParser::ParseTsv(rooms->at(i));
		std::string name = room_values->at(0);
		std::vector<std::string>* exits = FileParser::ParseCsv(room_values->at(2));
		std::vector<std::string>* directions = FileParser::ParseCsv(room_values->at(3));

		Room* room = dynamic_cast<Room*>(parent_.GetRooms().FindEntity(name));
		//room->Print();


		for (size_t j = 0; j != exits->size(); j++) {
			std::string exit_name = exits->at(j);
			std::string exit_dir = directions->at(j);

			Room* exit_room = dynamic_cast<Room*>(parent_.GetRooms().FindEntity(exit_name));

			if (exit_room)
			{
				room->AddExit(*exit_room);
				room->AddDirection(exit_room->GetId(), exit_dir);
			}
		}
	}
#ifdef _DEBUG_FLAG
	std::cout << "DONE" << std::endl;
#endif
#ifdef _DEBUG_FLAG
	std::cout << "DONE" << std::endl;
#endif
}

void Memento::LoadItems() {
	std::vector<std::string>* items = FileParser::ParseFile(items_file_);

	for (size_t i = 0; i < items->size(); ++i) {
		std::vector<std::string>* item_values = FileParser::ParseTsv(items->at(i));
		std::stringstream buffer(item_values->at(0));
		int id;
		if (!(buffer >> id)) {
			id = -1;
		}
		std::string name = item_values->at(1);

		Item* item = new Item(id, name, &parent_, id);

		std::vector<std::string>* shortnames = FileParser::ParseCsv(item_values->at(2));
		if (shortnames) {
			for (std::string shortName : *shortnames) {
				if (!shortName.empty()) {
					//std::cout << shortName << std::endl;
					item->AddShortName(shortName);
				}
			}
		}
		std::string desc = item_values->at(3);
		if (!desc.empty()) {
			item->SetDescription(desc);
		}

		parent_.GetItems().AddEntity(*item);
	}

}

/*
* Load mobs from a file
*/

void Memento::LoadMobs() {
	std::vector<std::string>* mobs = FileParser::ParseFile("mobs_file_");

	for (size_t i = 0; i < mobs->size(); ++i) {
		std::vector<std::string>* mob_values = FileParser::ParseTsv(mobs->at(i));
		std::stringstream buffer(mob_values->at(0));
		int id;
		if (!(buffer >> id)) {
			id = -1;
		}
		std::string name = mob_values->at(1);

		NPC* mob = new NPC(id, name, &parent_, id);

		std::string desc = mob_values->at(2);
		if (!desc.empty()) {
			mob->SetDescription(desc);
		}

		//std::cout << "New NPC: ID - " << id << ", Name - " << name << ", Description - " << desc << "\n";

		parent_.GetMasterMobs().AddEntity(*mob);
	}

}

/*
* Load classes from a file
*/
void Memento::LoadCharacterClasses() {
	std::vector<std::string>* classes = FileParser::ParseFile(character_classes_file_);

	for (size_t i = 0; i < classes->size(); ++i) {
		std::vector<std::string>* class_values = FileParser::ParseTsv(classes->at(i));

		std::stringstream buffer(class_values->at(0));
		int id;
		if (!(buffer >> id)) {
			id = -1;
		}
		std::string name = class_values->at(1);

		CharacterClass* class_ = new CharacterClass(id, name, &parent_);

		buffer.str(class_values->at(2));
		int health;
		if (!(buffer >> health)) {
			class_->SetHealth(health);
		}

		buffer.str(class_values->at(3));
		int mana;
		if (!(buffer >> mana)) {
			class_->SetMana(mana);
		}

		buffer.str(class_values->at(4));
		int strength;
		if (!(buffer >> strength)) {
			class_->SetStrength(strength);
		}

		buffer.str(class_values->at(5));
		int dexterity;
		if (!(buffer >> dexterity)) {
			class_->SetDexterity(dexterity);
		}

		buffer.str(class_values->at(6));
		int constitution;
		if (!(buffer >> constitution)) {
			class_->SetConstitution(constitution);
		}

		buffer.str(class_values->at(7));
		int intelligence;
		if (!(buffer >> intelligence)) {
			class_->SetIntelligence(intelligence);
		}

		buffer.str(class_values->at(8));
		int charisma;
		if (!(buffer >> charisma)) {
			class_->SetCharisma(charisma);
		}

		//std::cout << "New CLASS: ID - " << id << ", Name - " << name << ", Description - " << desc << "\n";

		parent_.GetCharacterClasses().AddCharacterClass(class_);
	}

}

void Memento::SavePlayers()
{
	std::ofstream file(players_file_);

	for (GameEntity* e : parent_.GetPlayers().GetEntityVector()) {
		Player* p = (Player*)e;
		std::stringstream playerOut;
		playerOut << p->GetName() << "\t";
		playerOut << p->GetPassword() << "\t";
		playerOut << p->GetRoomId() << "\t";

		playerOut << p->GetStats().GetMaxHealth() << ",";
		playerOut << p->GetStats().GetMaxMana() << ",";
		playerOut << p->GetStats().GetMaxStrength() << ",";
		playerOut << p->GetStats().GetMaxDexterity() << ",";
		playerOut << p->GetStats().GetMaxConstitution() << ",";
		playerOut << p->GetStats().GetMaxIntelligence() << ",";
		playerOut << p->GetStats().GetMaxCharisma() << "";

		playerOut << "\t";

		playerOut << p->GetDescription();

		playerOut << "\t";

		std::vector<GameEntity*> inventory = p->GetItemVector();
		if (!inventory.empty()) {
			if (inventory.size() == 1) {
				playerOut << ((Item*)inventory.at(0))->GetMasterId();
			}
			else {
				for (size_t i = 0; i < inventory.size() - 2; ++i) {
					playerOut << ((Item*)inventory.at(i))->GetMasterId() << ",";
				}
				playerOut << ((Item*)inventory.at(inventory.size() - 1))->GetMasterId();
			}

		}


		playerOut << "\n";

		file << playerOut.str();
	}
}