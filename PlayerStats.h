#pragma once

#include "Utility.h"
#include <string>
#include <sstream>

class PlayerStats
{
public:

	/**
	* Stat defaults - consider reading these in from a file somewhere,
	* and writing a command that sets them.
	*/
	const int iDefaultHealth = 50;
	const int iDefaultMana = 50;
	const int iDefaultStrength = 5;
	const int iDefaultDexterity = 5;
	const int iDefaultConstitution = 5;
	const int iDefaultIntelligence = 5;
	const int iDefaultCharisma = 5;

	PlayerStats();
	PlayerStats(const int MaxHealth, const int MaxMana, const int MaxStrength, const int MaxDexterity,
		const int MaxConstitution, const int MaxIntelligence, const int MaxCharisma);
	~PlayerStats();

	std::string Print();
	
	const int GetMaxHealth() const;
	const int GetHealth() const;
	void SetMaxHealth(const int newHealth);
	void SetHealth(const int newHealth);
	
	const int GetMaxMana() const;
	const int GetMana() const;
	void SetMaxMana(const int newMana);
	void SetMana(const int newMana);

	const int GetMaxStrength() const;
	const int GetStrength() const;
	void SetMaxStrength(const int newStrength);
	void SetStrength(const int newStrength);
	
	const int GetMaxDexterity() const;
	const int GetDexterity() const;
	void SetMaxDexterity(const int newDexterity);
	void SetDexterity(const int newDexterity);

	const int GetMaxConstitution() const;
	const int GetConstitution() const;
	void SetMaxConstitution(const int newConstitution);
	void SetConstitution(const int newConstitution);

	const int GetMaxIntelligence() const;
	const int GetIntelligence() const;
	void SetMaxIntelligence(const int newIntelligence);
	void SetIntelligence(const int newIntelligence);

	const int GetMaxCharisma() const;
	const int GetCharisma() const;
	void SetMaxCharisma(const int newCharisma);
	void SetCharisma(const int newCharisma);

	void SetStats(const int hp, const int mp, const int str, const int dex, const int con, const int int_, const int cha);

private:
	int mHealth, mTempHealth;
	int mMana, mTempMana;
	int mStrength, mTempStrength;
	int mDexterity, mTempDexterity;
	int mConstitution, mTempConstitution;
	int mIntelligence, mTempIntelligence;
	int mCharisma, mTempCharisma;
};