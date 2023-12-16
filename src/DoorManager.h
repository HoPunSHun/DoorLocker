#pragma once

#include <string>
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
	void OpenDoorWithPassword(const std::string &password);
	void UpdateDoorOpenHistory(const Card &card);
	void UpdateDoorOpenHistory();

	void SetPassword(const std::string &password);

	void AddCard(const std::string &name, int sex, int securityCodeLevel);
	void RemoveCard(const int id);
	void RemoveCard(const std::string &cardName);
	bool CheckCard(const Card &card);

	void SetCard(const std::string &cardName, const Card &card);
	void SetCard(int id, const Card &card);

	const std::string GenerateSecurityCode(int numOfChar);
	
	void ListCardInfo();
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

	bool CheckSameCardName(const std::string &cardName);

	void FILEOPENERROR(const std::string &fileName);

private:

	int m_nextId;

	std::map<int, Card> m_cardsId;
	std::map<std::string, Card> m_cardsName;

	std::string m_password;

	std::vector<History> m_doorOpenHistory;

	bool m_cardInfoChanged = false;
	bool m_doorOpenHistoryChanged = false;
	bool m_passwordChanged = false;

};
