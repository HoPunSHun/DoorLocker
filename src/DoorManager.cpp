#include "DoorManager.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <chrono>
#include <conio.h>

DoorManager::DoorManager()
	:	m_nextId	(0)
{}

void DoorManager::Init()
{

	ReadCardInfo();
	ReadDoorOpenHistory();	
	ReadPassword();	

	m_currentMenu = "MainMenu";

	m_menu["MainMenu"] = Menu("MainMenu");

	m_menu[m_currentMenu].PrintMenu();

	Exit();

}

int DoorManager::InputOption(const std::string &inputMsg)
{

	std::cout << inputMsg << "(number):";

	int option = -1;

	while (option == -1)
	{

		std::string input;

		std::cin >> input;

		std::istringstream translater(input);

		if (!(translater >> option))
		{

			option = -1;

			std::cout << inputMsg << "(number)(Invalid Number):";

		}

	}

	return option;

}

const std::string DoorManager::InputText(const std::string &msg)
{

	std::string inputText;

	std::cout << msg << ':';
	std::cin >> inputText;

	return inputText;

}

void DoorManager::ClearTerminal()
{

	std::cout << "\033[2J\033[1;1H";

}

void DoorManager::OpenDoorWithCard(const std::string &cardName)
{

	Card card;

	std::string cardPath = "data/Cards/" + cardName + ".txt";

	ReadCardInfo(cardPath, card);

	if (CheckCard(card))
	{

		UpdateDoorOpenHistory(card.GetName());

		std::cout << "Welcome. Door opened successfully" << '\n';	

		m_doorOpenHistoryChanged = true;

	}
	else
	{

		std::cout << "Unable to open. Unregister card" << '\n';

	}

}

void DoorManager::OpenDoorWithPassword(const std::string &password)
{

	if (password == m_password)
	{

		std::cout << "Welcome. Door opened successfully" << '\n';	
		UpdateDoorOpenHistory("Password");

		m_doorOpenHistoryChanged = true;

	}
	else
	{

		std::cout << "Password incorrect" << '\n';

	}

}

void DoorManager::UpdateDoorOpenHistory(const std::string& name)
{

	std::string time_y, time_mon, time_d, time_h, time_m;

	std::chrono::time_point nowTP = std::chrono::system_clock::now();

	std::time_t nowTT = std::chrono::system_clock::to_time_t(nowTP);

	std::tm nowTM = *(std::localtime(&nowTT));

	int year = 1900 + nowTM.tm_year;
	int mon = 1 + nowTM.tm_mon;
	int day = nowTM.tm_mday;
	int hour = nowTM.tm_hour;
	int min = nowTM.tm_min;
	int sec = nowTM.tm_sec;
	int weekDay = nowTM.tm_wday;

	History newHistory(name, year, mon, day, hour, min, sec, weekDay);

	m_doorOpenHistory.push_back(newHistory);

}

void DoorManager::ReadPassword()
{

	std::fstream file;

	file.open("data/password.txt", std::ios::in);

	if (file.is_open())
	{

		file >> m_password;

	}
	else
	{

		m_password = "";

	}

}

void DoorManager::SetPassword(const std::string &password)
{

	bool allNum = true;

	for (char letter : password)
	{

		int asNum = letter;

		if (!(asNum > 47 && asNum < 58))
		{

			std::cout << "Password must be created by numbers" << '\n';
			allNum = false;

		}	

	}

	if (password.length() > 3 && allNum)
	{

		m_password = password;	
		m_passwordChanged = true;

	}
	else
	{

		std::cout << "Password must be more then 3 digit and all of them must be numbers" << '\n';

	}

}

void DoorManager::SavePassword()
{

	CreateFileAndWrite("data/password.txt", m_password);	

}

void DoorManager::RegisterCard(const std::string &name, int sex, int securityCodeLevel)
{

	if (!CheckSameCardName(name))
	{

		std::string securityCode = GenerateSecurityCode(securityCodeLevel);

		std::string cardPath = "data/Cards/" + name + ".txt";

		Card card(name, sex, m_nextId, securityCode);	

		m_cardsId[m_nextId] = card;
		m_cardsName[name] = card;

		CreateFileAndWrite(cardPath, name + ' ' + std::to_string(sex) + ' ' + std::to_string(m_nextId) + ' ' + securityCode);

		m_nextId++;	

		m_cardInfoChanged = true;

	}
	else
	{

		std::cout << "Card already exist" << '\n';

	}

}

void DoorManager::RemoveCard(const int id)
{

	m_cardsName.erase(m_cardsId[id].GetName());
	m_cardsId.erase(id);	

	m_cardInfoChanged = true;

}

void DoorManager::RemoveCard(const std::string &cardName)
{

	m_cardsId.erase(m_cardsName[cardName].GetId());
	m_cardsName.erase(cardName);

	m_cardInfoChanged = true;

}

bool DoorManager::CheckCard(const Card &card)
{
	
	bool result = (card == m_cardsId[card.GetId()]) ? true : false;

	return result;

}

void DoorManager::SetCard(const std::string &cardName, const Card &_card)
{

	if (m_cardsName.find(cardName) != m_cardsName.end())
	{

		m_cardsName[cardName].SetAs(_card);
		m_cardsId[m_cardsName[cardName].GetId()].SetAs(_card);

	}
	else
	{

		std::cout << "Card doesn't exist" << '\n';

	}

	m_cardInfoChanged = true;

}

void DoorManager::SetCard(int id, const Card &_card)
{

	if (m_cardsId.find(id) != m_cardsId.end())
	{

		m_cardsId[id].SetAs(_card);
		m_cardsName[m_cardsId[id].GetName()].SetAs(_card);

	}
	else
	{

		std::cout << "Card doesn't exist" << '\n';

	}

	m_cardInfoChanged = true;

}

const std::string DoorManager::GenerateSecurityCode(int numOfChar)
{

	std::string code;

	for (int i = 0; i < numOfChar; i++)
	{

		int dec = (rand() % (128 - 33)) + 33;
		code += char(dec);

	}


	return code;

}

void DoorManager::ListCardInfo()
{

	int loopCount = 1;

	for (auto it = m_cardsId.begin(); it != m_cardsId.end(); it++)
	{

		Card card = it->second;

		std::cout << loopCount << '.' << card.GetName() << ' ' << card.GetSex() << ' ' << card.GetId() << ' ' << card.GetSecurityCode() << '\n';

		loopCount++;

	}

}

void DoorManager::ListDoorOpenHistory()
{

	for (const auto &history : m_doorOpenHistory)
	{

		std::cout << history.GetName() << ' ' << history.GetTime() << '\n';

	}

}

void DoorManager::ReadDoorOpenHistory()
{

	std::fstream file;
	file.open("data/DoorOpenHistory.txt", std::ios::in);

	if (file.is_open())
	{

		std::string name;

		while (file >> name) 
		{

			History history;

			int year, mon, day, hour, min, sec, weekDay;

			file >> year >> mon >> day >> hour >> min >> sec >> weekDay;

			history = History(name, year, mon, day, hour, min, sec, weekDay);

			m_doorOpenHistory.push_back(history);
	
		}		
	
	}
	else
	{

		CreateFile("data/DoorOpenHistory.txt");

	}

	file.close();

}

void DoorManager::ReadCardInfo(const std::string &cardPath, Card &card)
{

	std::fstream file;	

	file.open(cardPath, std::ios::in);

	if (file.is_open())
	{

		std::string name, securityCode;

		int sex, id;

		file >> name >> sex >> id >> securityCode;

		card = Card(name, sex, id, securityCode);

	}
	else
	{

		FILEOPENERROR(cardPath);

	}

	file.close();

}

void DoorManager::ReadCardInfo()
{

	std::fstream file;

	file.open("data/CardInfo.txt", std::ios::in);

	if (file.is_open())
	{

		file >> m_nextId;

		std::string name;

		while (file >> name)
		{		

			int sex, id;

			std::string securityCode;

			file >> sex >> id >> securityCode;	

			Card card(name, sex, id, securityCode);

			m_cardsId[id] = card;
			m_cardsName[name] = card;

		}

	}
	else
	{

		CreateFileAndWrite("data/CardInfo.txt", "0");

	}

}

void DoorManager::SaveDoorOpenHistory()
{

	std::fstream file;
	file.open("data/DoorOpenHistory.txt", std::ios::out | std::ios::trunc);

	if (file.is_open())
	{

		for (const auto& history : m_doorOpenHistory)
		{

			file << history.GetName() << ' ' << history.GetTime() << '\n';;
			
		}

	}
	else
	{

		FILEOPENERROR("data/DoorOpenHistory.txt");

	}

}

void DoorManager::SaveCardInfo()
{

	std::fstream file;

	file.open("data/CardInfo.txt", std::ios::out | std::ios::trunc);

	if (file.is_open())
	{
	
		file << m_nextId << '\n';

		for (auto it = m_cardsId.begin(); it != m_cardsId.end(); it++)
		{

			Card _card = it->second;

			std::string name = _card.GetName();
			std::string securityCode = _card.GetSecurityCode();

			int sex = _card.GetSex();
			int id = _card.GetId();

			file << name << ' ' << sex << ' ' << id << ' ' << securityCode << '\n';

		}
	

	}

	file.close();

}

void DoorManager::Exit()
{

	if (m_doorOpenHistoryChanged) 
	{ 

		std::cout << "Saving Door Open Histories" << '\n';		
		SaveDoorOpenHistory(); 
	
	}

	if (m_cardInfoChanged)	
	{ 
		
		std::cout << "Saving Card Informations" << '\n';
		SaveCardInfo(); 
	
	}

	if (m_passwordChanged)
	{

		std::cout << "Saving password" << '\n';
		SavePassword();

	}

}

void DoorManager::CreateFile(const std::string &filePath)
{

	std::fstream file;
	file.open(filePath, std::ios::out);
	file.close();

}

void DoorManager::CreateFileAndWrite(const std::string &filePath, const std::string &line)
{

	std::fstream file;
	file.open(filePath, std::ios::out | std::ios::trunc);
	file << line;
	file.close();

}

bool DoorManager::CheckSameCardName(const std::string &cardName)
{

	if (m_cardsName.find(cardName) != m_cardsName.end())
	{

		return true;

	}

	return false;

}

void DoorManager::FILEOPENERROR(const std::string &fileName)
{

	std::cout << "Unable to open file '"  << fileName << "'\n";

}
