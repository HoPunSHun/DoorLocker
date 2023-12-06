#pragma once
#include <map>
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

	void CopyCardInfoToFile();

	bool CheckCard(const std::string &cardPath);

	void SetCard(const Card &card);

	void SaveNextId();

	void FILEOPENERROR(const std::string &fileName);

private:

	int m_numOfCards;

	int m_nextId;

	std::map<std::string, Card> m_cards;

};
