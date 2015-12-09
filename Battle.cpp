#include "Battle.h"

Battle::Battle(int id, GameWorld* parent) :
	parent_(*parent),
	id_(id)
{
}


Battle::~Battle()
{
}

bool Battle::IsParticipant(GameEntity* p) const {
	
	std::cout << "Is " << p->GetName() << " a member of Battle " << id_ << "?\n";
	// check players
	std::map<int, Player*>::const_iterator pIt = players_.find(p->GetId());
	if (pIt != players_.end()) {
		if (pIt->second == (Player*) p) {
			std::cout << "Yes\n";
			return true;
		}
	}

	// check mobs
	std::map<int, NPC*>::const_iterator mIt = mobs_.find(p->GetId());
	if (mIt != mobs_.end()) {
		if (mIt->second == (NPC*)p) {
			std::cout << "Yes\n";
			return true;
		}
	}

	// otherwise nope
	std::cout << "No\n";
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

bool Battle::IsEmpty() const
{
	if (players_.empty() && mobs_.empty())
		return true;
	return false;
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
		for (std::map<GameEntity*, GameEntity*>::iterator it = targets_.find(p); it != targets_.end(); it = targets_.find(p)) {
			targets_.erase(it->first);
		}
		for (std::map<GameEntity*, GameEntity*>::iterator it = targets_.begin(); it != targets_.end(); it++) {
			if (it->second == p) {
				it->second = nullptr;
			}
		}
	}
}

void Battle::MobFlee(GameEntity* p) {
	if (IsParticipant(p)) {

		// insert flee calculation logic here

		mobs_.erase(p->GetId());
		for (std::map<GameEntity*, GameEntity*>::iterator it = targets_.find(p); it != targets_.end(); it = targets_.find(p)) {
			targets_.erase(it->first);
		}
		for (std::map<GameEntity*, GameEntity*>::iterator it = targets_.begin(); it != targets_.end(); it++) {
			if (it->second == p) {
				it->second = nullptr;
			}
		}
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
	// If there are no players or no NPCs remaining, end the battle
	if (players_.empty() || mobs_.empty()) {
		parent_.GetBattles().DeleteBattle(id_);
	}

	// loop through each participant and calculate their attack.
	for (std::pair<int, Player*> pair : players_) {
		Player* p = pair.second;
		NPC* t = (NPC*) targets_.at(p);

		if (!IsParticipant(t)) {
			SetTarget(p, mobs_.begin()->second);
			t = mobs_.begin()->second;
		}

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		engine_ = std::default_random_engine(seed);

		std::uniform_int_distribution<int> playerDist(1, 10);
		int playerRoll = playerDist(engine_) + p->GetStats().GetDexterity();
		std::uniform_int_distribution<int> mobDist(1, 10);
		int mobRoll = mobDist(engine_) + t->GetStats().GetDexterity();

		if (playerRoll > mobRoll) {
			std::stringstream outString;
			outString << "You hit " << cGreen << t->GetName() << cDefault << " for " << cRed << p->GetStats().GetStrength() << cDefault << " damage.";
			// this next line is for debug only
			//outString << "\n(" << t->GetStats().GetHealth() - p->GetStats().GetStrength() << " remaining)";
			Message* playerMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
			parent_.GetParent().PutMessage(playerMsg);
			if (t->Damage(p->GetStats().GetStrength()) == 1) {
				t->Die();
				/* This should really be the die code, but we need accessors for GameWorld and Room and shit first */
				Room* r = (Room*)parent_.GetRoom(t->GetRoomId());
				r->RemoveMob(t->GetId());
				/* Derp */
				outString.str("");
				outString << cGreen << t->GetName() << cDefault << " dies." << cDefault;
				Message* mobDieMsg = new Message(outString.str(), p->GetConnectionId(), Message::outputMessage);
				parent_.GetParent().PutMessage(mobDieMsg);
				MobFlee(t);
			}
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

		if (!IsParticipant(t)) {
			SetTarget(p, players_.begin()->second);
			t = players_.begin()->second;
		}

		std::uniform_int_distribution<int> playerDist(1, 10);
		int playerRoll = playerDist(engine_) + t->GetStats().GetDexterity();
		std::uniform_int_distribution<int> mobDist(1, 10);
		int mobRoll = mobDist(engine_) + p->GetStats().GetDexterity();

		if (mobRoll > playerRoll) {
			std::stringstream outString;
			outString << cGreen << p->GetName() << cDefault << " hits you for " << cRed << p->GetStats().GetStrength() << cDefault << " damage.";
			Message* playerMsg = new Message(outString.str(), t->GetConnectionId(), Message::outputMessage);
			parent_.GetParent().PutMessage(playerMsg);
			if (t->Damage(p->GetStats().GetStrength()) == 1) {
				outString.str("");
				outString << cRed << "You die." << cDefault;
				Message* playerDieMsg = new Message(outString.str(), t->GetConnectionId(), Message::outputMessage);
				parent_.GetParent().PutMessage(playerDieMsg);
				p->Die();
				/* This should also be the die code. */
				Room* r = parent_.FindPlayerRoom(*t);
				r->RemovePlayer(t->GetId());
				t->GetStats().SetHealth(t->GetStats().GetMaxHealth());
				t->GetStats().SetMana(t->GetStats().GetMaxMana());
				t->SetRoomId(0);
				r = (Room*)parent_.GetRoom(0);
				r->AddPlayer(*t);
				/* end of derpy die code */
				parent_.Look(t->GetConnectionId());
				PlayerFlee(t);
			}
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