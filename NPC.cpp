#include "NPC.h"



NPC::NPC(int id, std::string name, GameWorld* world, int master) : GameEntity(id, name, world),
	master_id_(master),
	stats_(new PlayerStats())
{
}

/**Create an NPC with an ID and another NPC to copy from */
NPC::NPC(int newId, const NPC& other) : GameEntity(newId, other.GetName(), other.GetDescription(), &(other.GetWorld())),
	master_id_(other.GetMasterId()),
	stats_(new PlayerStats())
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

int NPC::Damage(const int damage) {
	stats_->SetHealth(stats_->GetHealth() - damage);
	if (stats_->GetHealth() <= 0) {
		return 1;
	}
	return 0;
}

void NPC::Die() {

}
