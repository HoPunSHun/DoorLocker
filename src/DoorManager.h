#pragma once
#include <vector>

#include "Card.h"

class DoorManager
{

public:

	DoorManager(){}

	void Init();

	void ListCards();

private:

	void ReadCardInfo();

	void FILEOPENERROR(const char* fileName);

private:

	int m_numOfCards;

	std::vector<Card> m_cards;

};
