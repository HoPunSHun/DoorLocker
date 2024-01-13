#pragma once

#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <functional>

#include "History.h"
#include "Card.h"
#include "Menu.h"

class DoorManager
{

public:

	DoorManager();

	void Init();
	
private:

	void InitMenu();

	void MainLoop();

	void Exit();

	void UserOpenDoor();
	void UserGetCardInfo();
	void UserGetDoorOpenHistory();
	void UserRegisterCard();
	void UserDeleteCard();
	void UserDeleteHistory();

	int InputOption(const std::string &msg);
	const std::string InputText(const std::string &msg);

	void PrintMsgAndWait(const std::string &msg);

	void ClearTerminal();

	void OpenDoorWithCard(const std::string &cardName);
	void OpenDoorWithPassword(const std::string &password);
	void UpdateDoorOpenHistory(const std::string &type);

	void ReadPassword();
	void SetPassword(const std::string &password);
	void SavePassword();

	void RegisterCard(const std::string &name, int sex, int securityCodeLevel);
	void DeleteCard(const int id);
	void DeleteCard(const std::string &cardName);
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

	void SaveData();

	void SaveDoorOpenHistory();

	void SaveCardInfo();

	void SaveNextId();

	void CreateFile(const std::string &filePath);
	void CreateFileAndWrite(const std::string &filePath, const std::string &line);

	bool CheckSameCardName(const std::string &cardName);

	void FILEOPENERROR(const std::string &fileName);

private:

	std::string m_currentMenu;

	std::map<std::string, Menu> m_menu;

	int m_nextId;

	std::map<int, Card> m_cardsId;
	std::map<std::string, Card> m_cardsName;

	std::string m_password;

	std::vector<History> m_doorOpenHistory;

	bool m_cardInfoChanged = false;
	bool m_doorOpenHistoryChanged = false;
	bool m_passwordChanged = false;

};
