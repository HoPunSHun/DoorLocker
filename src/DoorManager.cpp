#include "DoorManager.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

DoorManager::DoorManager()
	:	m_nextId	(0)
{}

void DoorManager::Init()
{

	ReadCardInfo();
	ReadDoorOpenHistory();	

	ListDoorOpenHistory();

	SaveDoorOpenHistory();
	SaveCardInfo();

}

void DoorManager::OpenDoorWithCard(const std::string &cardName)
{

	Card card;

	std::string cardPath = "data/" + cardName + ".txt";

	ReadCardInfo(cardPath, card);

	if (CheckCard(card))
	{

		UpdateDoorOpenHistory(card);

		std::cout << "Welcome. Door opened successfully" << '\n';	

	}
	else
	{

		std::cout << "Unable to open. Unregister card" << '\n';

	}

}

void DoorManager::UpdateDoorOpenHistory(const Card &card)
{

	int time_h = 13;
	int time_m = 56;

	History newHistory(card.GetName(), time_h, time_m);

	m_doorOpenHistory.push_back(newHistory);

}

void DoorManager::AddCard(const std::string &name, int sex, int securityCodeLevel)
{

	if (m_cards.find(name) == m_cards.end())
	{

		std::string securityCode = GenerateSecurityCode(securityCodeLevel);

		std::string cardPath = "data/" + name + ".txt";

		Card card(name, sex, m_nextId, securityCode);	

		m_cards[name] = card;

		CreateFileAndWrite(cardPath, name + ' ' + std::to_string(sex) + ' ' + std::to_string(m_nextId) + ' ' + securityCode);

		m_nextId++;	

	}
	else
	{

		std::cout << "Card already exist" << '\n';

	}

}

void DoorManager::RemoveCard(const std::string &name)
{

	m_cards.erase(name);	

}

const std::string DoorManager::GenerateSecurityCode(int numOfChar)
{

	std::string code;

	for (int i = 0; i < numOfChar; i++)
	{

		code += char((rand() % (127 - 21)) + 21);

	}


	return code;

}

void DoorManager::GetNextId()
{

	int *ids = new int[m_cards.size()];

	int numOfCards = 0;

	for (auto it = m_cards.begin(); it != m_cards.end(); it++)
	{

		ids[numOfCards] = it->second.GetId();

		numOfCards++;

	}

	for (int j = 0; j < m_cards.size() - 1; j++)
	{

		if (ids[j] > ids[j + 1])
		{
			
			int tmp = ids[j];

			ids[j] = ids[j + 1];
			ids[j + 1] = tmp;

		}

	}


	m_nextId = ++ids[numOfCards - 1];

	delete []ids;

}

bool DoorManager::CheckCard(const Card &card)
{
	
	bool result = (card == m_cards[card.GetName()]) ? true : false;

	return result;

}

void DoorManager::SetCard(const Card &card)
{

	for (auto it = m_cards.begin(); it != m_cards.end(); it++)
	{

		Card _card = it->second;

		if (_card.GetId() == card.GetId())
		{

			_card = card;			

		}

	}

}

void DoorManager::ListCards()
{

	int loopCount = 1;

	for (auto it = m_cards.begin(); it != m_cards.end(); it++)
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

		std::string type;

		while (file >> type)
		{

			History history;

			int time_h, time_m;

			file >> time_h >> time_m;	

			if (type != "Password")
			{

				history = History(type, time_h, time_m);

			}
			else
			{

				history = History(time_h, time_m);

			}

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
	
		std::string name;

		while (file >> name)
		{		

			int sex, id;

			std::string securityCode;

			file >> sex >> id >> securityCode;	

			m_cards[name] = Card(name, sex, id, securityCode);

		}

	}
	else
	{

		CreateFile("data/CardInfo.txt");

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

			file << history.GetName() << ' ' << history.GetHour() << ' ' << history.GetMinute() << '\n';
			
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
		
		for (auto it = m_cards.begin(); it != m_cards.end(); it++)
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

void DoorManager::CreateFile(const std::string &filePath)
{

	std::fstream file;
	file.open(filePath, std::ios::out);
	file.close();

}

void DoorManager::CreateFileAndWrite(const std::string &filePath, const std::string &line)
{

	std::fstream file;
	file.open(filePath, std::ios::out);
	file << line;
	file.close();

}

void DoorManager::FILEOPENERROR(const std::string &fileName)
{

	std::cout << "Unable to open file '"  << fileName << "'\n";

}
