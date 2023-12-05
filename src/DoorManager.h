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
		
private:

	void ReadNextId();

	void ReadCardInfo();

	void CopyFile(std::fstream &file, std::vector<std::string> &lines);

	void CopyToFile(std::fstream &file, const std::vector<std::string> &lines);

	void FILEOPENERROR(const char* fileName);

	void SaveNextId();

private:

	int m_numOfCards;

	int m_nextId;

	std::vector<Card> m_cards;

};
