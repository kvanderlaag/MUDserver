#include "NPC.h"



NPC::NPC(int id, std::string name, GameWorld* world, int master) : GameEntity(id, name, world),
	master_id_(master)
{
}

/**Create an NPC with an ID and another NPC to copy from */
NPC::NPC(int newId, const NPC& other) : GameEntity(newId, other.GetName(), other.GetDescription(), &(other.GetWorld())),
	master_id_(other.GetMasterId())
{
}


NPC::~NPC()
{
}

PlayerStats& NPC::GetStats() const {
	return *(stats_.get());
}

EntityList& NPC::GetItems() const {
	return *(items_.get());
}

int NPC::GetMasterId() const {
	return master_id_;
}
