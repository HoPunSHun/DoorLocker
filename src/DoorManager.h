#pragma once
#include <map>
#include <vector>

#include "Card.h"
#include "History.h"

class DoorManager
{

public:

	DoorManager();

	void Init();
	
private:

	void OpenDoorWithCard(const std::string &cardName);
	void UpdateDoorOpenHistory(const Card &card);

	void AddCard(const std::string &name, int sex, int securityCodeLevel);
	void RemoveCard(const std::string &name);

	const std::string GenerateSecurityCode(int numOfChar);

	void GetNextId();

	bool CheckCard(const Card &card);

	void SetCard(const Card &card);

	void ListCards();
	void ListDoorOpenHistory();

	void ReadDoorOpenHistory();

	void ReadNextId();

	void ReadCardInfo(const std::string &cardPath, Card &card);
	
	void ReadCardInfo();

	void SaveDoorOpenHistory();

	void SaveCardInfo();

	void SaveNextId();

	void CreateFile(const std::string &filePath);
	void CreateFileAndWrite(const std::string &filePath, const std::string &line);

	void FILEOPENERROR(const std::string &fileName);

private:

	int m_numOfCards;

	int m_nextId;

	std::map<std::string, Card> m_cards;

	std::vector<History> m_doorOpenHistory;

};
