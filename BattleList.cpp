#include "BattleList.h"


BattleList::BattleList(GameWorld * world) :
	parent_(*world)
{
	next_ids_.push_back(0);
}

BattleList::~BattleList()
{
}

int BattleList::GetNextId()
{
	int id = next_ids_.back();

	next_ids_.pop_back();

	// if its empty, push id+1 onto it
	if (next_ids_.size() == 0)
	{
		next_ids_.push_back(battles_.size());
	}

	return id;
}

void BattleList::PutNextId(int nextId)
{
	next_ids_.push_back(nextId);
}

void BattleList::Update()
{
	for (std::pair<int, Battle*> bPair : battles_) {
		Battle* b = bPair.second;
		if (b->IsEmpty()) {
			DeleteBattle(b);
			delete b;
		}
		else {
			b->Update();
		}
	}
}

void BattleList::AddBattle(Battle * b)
{
	battles_.insert(std::pair<int, Battle*>(b->GetId(), b));
}

void BattleList::DeleteBattle(Battle * b)
{
	battles_.erase(b->GetId());
}

void BattleList::DeleteBattle(int id)
{
	battles_.erase(id);
}

Battle * BattleList::GetBattleByPlayerName(std::string name)
{
	GameEntity* p = GetParent().GetPlayers().FindEntity(name);
	if (p) {
		for (std::pair<int, Battle*> pair : battles_) {
			Battle* b = pair.second;
			if (b->IsParticipant(p)) {
				return b;
			}
		}
	}
	return nullptr;
}

Battle * BattleList::GetBattleByPlayerId(int id)
{
	GameEntity* p = GetParent().GetPlayers().GetEntity(id);

	if (p) {
		for (std::pair<int, Battle*> pair : battles_) {
			Battle* b = pair.second;
			if (b->IsParticipant(p)) {
				return b;
			}
		}
	}
	return nullptr;
}

Battle * BattleList::GetBattleByMobName(std::string name)
{
	GameEntity* p = GetParent().GetMobs().FindEntity(name);
	if (p) {
		for (std::pair<int, Battle*> pair : battles_) {
			Battle* b = pair.second;
			if (b->IsParticipant(p)) {
				return b;
			}
		}
	}
	return nullptr;
}

Battle * BattleList::GetBattleByMobId(int id)
{
	GameEntity* p = GetParent().GetMobs().GetEntity(id);

	if (p) {
		for (std::pair<int, Battle*> pair : battles_) {
			Battle* b = pair.second;
			if (b->IsParticipant(p)) {
				return b;
			}
		}
	}
	return nullptr;
}

GameWorld & BattleList::GetParent() const
{
	return parent_;
	// TODO: insert return statement here
}
