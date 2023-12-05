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

	void ReadCardInfo(const std::string &cardPath, Card &card);

	void CopyFile(std::fstream &file, std::vector<std::string> &lines);

	void CopyToFile(std::fstream &file, const std::vector<std::string> &lines);

	bool CheckCard(const std::string &cardPath);

	void SaveNextId();

	void FILEOPENERROR(const std::string &fileName);

private:

	int m_numOfCards;

	int m_nextId;

	std::vector<Card> m_cards;

};
