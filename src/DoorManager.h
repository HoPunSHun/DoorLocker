#pragma once
#include <vector>

#include "Card.h"

class DoorManager
{

public:

	DoorManager();

	void Init();

	void ListCards();

	void AddCard(const std::string &name, int sex, int securityCodeLevel);

	const std::string GenerateSecurityCode(int numOfChar);
	
	void SaveNextId();

private:

	void ReadNextId();

	void ReadCardInfo();

	void SaveNewCard(const Card &card);

	void FILEOPENERROR(const char* fileName);

private:

	int m_numOfCards;

	int m_nextId;

	std::vector<Card> m_cards;

};
