#include "Battle.h"

Battle::Battle(int id, GameWorld* parent) :
	parent_(*parent)
{
}


Battle::~Battle()
{
}

bool Battle::IsParticipant(GameEntity* p) const {
	
	// check players
	for (std::pair<int, Player*> pair : players_) {
		if (pair.second == (Player*) p) {
			return true;
		}
	}

	// check mobs
	for (std::pair<int, NPC*> pair : mobs_) {
		if (pair.second == (NPC*) p) {
			return true;
		}
	}

	// otherwise nope
	return false;
}

NPC * Battle::GetMobByName(std::string name)
{
	for (std::pair<int, NPC*> pair : mobs_) {
		std::string lowerName(pair.second->GetName());
		for (std::string::iterator it = lowerName.begin(); it != lowerName.end(); it++) {
			*it = std::tolower(*it);
		}

		for (std::string::iterator it = name.begin(); it != name.end(); it++) {
			*it = std::tolower(*it);
		}
	
		if (lowerName == name) {
			return pair.second;
		}
	}
	return nullptr;
}

Player * Battle::GetPlayerByName(std::string name)
{
	for (std::pair<int, Player*> pair : players_) {
		std::string lowerName(pair.second->GetName());
		for (std::string::iterator it = lowerName.begin(); it != lowerName.end(); it++) {
			*it = std::tolower(*it);
		}

		for (std::string::iterator it = name.begin(); it != name.end(); it++) {
			*it = std::tolower(*it);
		}

		if (lowerName == name) {
			return pair.second;
		}
	}
	return nullptr;
}

void Battle::AddPlayer(GameEntity* p, GameEntity* target) {
	if (!IsParticipant(p)) {
		players_.insert(std::pair<int, Player*>(p->GetId(), (Player*) p));
		targets_.insert(std::pair<GameEntity*, GameEntity*>(p, target));
	}
}

void Battle::AddMob(GameEntity* p, GameEntity* target) {
	if (!IsParticipant(p)) {
		mobs_.insert(std::pair<int, NPC*>(p->GetId(), (NPC*) p));
		targets_.insert(std::pair<GameEntity*, GameEntity*>(p, target));
	}
}

void Battle::PlayerFlee(GameEntity* p) {
	if (IsParticipant(p)) {

		// insert flee calculation logic here

		players_.erase(p->GetId());
	}
}

void Battle::MobFlee(GameEntity* p) {
	if (IsParticipant(p)) {

		// insert flee calculation logic here

		mobs_.erase(p->GetId());
	}
}

const int Battle::GetId() const {
	return id_;
}

void Battle::SetTarget(GameEntity* p, GameEntity* target) {
	if (IsParticipant(p) && IsParticipant(target)) {
		targets_.at(p) = target;
	}
}

void Battle::Update() {
	// loop through each participant and calculate their attack.
	for (std::pair<int, Player*> pair : players_) {
		Player* p = pair.second;
		NPC* t = (NPC*) targets_.at(p);

		std::uniform_int_distribution<int> playerDist(1, p->GetStats().GetDexterity());
		int playerRoll = playerDist(engine_);
		std::uniform_int_distribution<int> mobDist(1, t->GetStats().GetDexterity());
		int mobRoll = mobDist(engine_);

		if (playerRoll > mobRoll) {
			std::stringstream outString;
			outString << "You hit " << cGreen << t->GetName() << cDefault << " for " << cRed << p->GetStats().GetStrength() << cDefault << " damage.";
			Message* playerMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
			parent_.GetParent().PutMessage(playerMsg);
		}
		else {
			std::stringstream outString;
			outString << "You missed " << cGreen << t->GetName() << cDefault << ".";
			Message* playerMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
			parent_.GetParent().PutMessage(playerMsg);
		}
	}

	for (std::pair<int, NPC*> pair : mobs_) {
		NPC* p = pair.second;
		Player* t = (Player*) targets_.at(p);

		std::uniform_int_distribution<int> playerDist(1, t->GetStats().GetDexterity());
		int playerRoll = playerDist(engine_);
		std::uniform_int_distribution<int> mobDist(1, p->GetStats().GetDexterity());
		int mobRoll = mobDist(engine_);

		if (mobRoll > playerRoll) {
			std::stringstream outString;
			outString << cGreen << t->GetName() << cDefault << " hits you for " << cRed << p->GetStats().GetStrength() << cDefault << " damage.";
			Message* playerMsg = new Message(outString.str(), t->GetConnectionId(), Message::outputMessage);
			parent_.GetParent().PutMessage(playerMsg);
		}
		else {
			std::stringstream outString;
			outString << cGreen << p->GetName() << cDefault << " misses you.";
			Message* playerMsg = new Message(outString.str(), t->GetConnectionId(), Message::outputMessage);
			parent_.GetParent().PutMessage(playerMsg);
		}
	
	}
}

GameWorld& Battle::GetParent() const {
	return parent_;
}