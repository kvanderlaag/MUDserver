#include "Memento.h"

Memento::Memento(GameWorld & world) :
	parent_(world)
{
}

Memento::~Memento()
{
}

EntityList & Memento::GetState()
{
	FileParser::ParseTsv();
	return EntityList();

}

void Memento::SetState(EntityList & players)
{
	FileParser::WritePlayers("players.tsv", players.GetEntityVector());
}