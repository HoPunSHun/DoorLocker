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

	GetNextId();

	std::cout << m_nextId << '\n';

}

void DoorManager::AddCard(const std::string &name, int sex, int securityCodeLevel)
{

	std::string securityCode = GenerateSecurityCode(securityCodeLevel);

	std::string cardPath = std::string("data/") + name + ".txt";

	Card card(name, sex, m_nextId, GenerateSecurityCode(securityCodeLevel));	

	m_cards[name] = card;

	std::fstream file;

	file.open("data/CardInfo.txt", std::ios::in | std::ios::app);

	file << '\n' << name << ' ' << sex << ' ' << m_nextId <<  ' ' << securityCode;

	file.close();

	file.open(cardPath, std::ios::out | std::ios::trunc);

	file << name << ' ' << sex << ' ' << m_nextId << ' ' << securityCode;

	file.close();

	m_nextId++;

	SaveNextId();

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

	for (int i = m_cards.size() - 1; i > numOfCards; i--)
	{

		for (int j = 0; j < i; j++)
		{

			if (ids[j] > ids[j + 1])
			{
			
				int tmp = ids[j];

				ids[j] = ids[j + 1];
				ids[j + 1] = tmp;

			}

		}

	}

	m_nextId = ++ids[numOfCards - 1];

	delete []ids;

}

bool DoorManager::CheckCard(const std::string& cardPath)
{

	Card card;

	ReadCardInfo(cardPath, card);
	
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

void DoorManager::ReadNextId()
{

	std::fstream file;

	file.open("data/NextId.txt", std::ios::in);

	if (file.is_open())
	{

		file >> m_nextId;	

	}
	else
	{

		FILEOPENERROR("data/NextId.txt");

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

		m_numOfCards = 0;
	
		std::string name;

		while (file >> name)
		{		

			int sex, id;

			std::string securityCode;

			file >> sex >> id >> securityCode;	

			m_cards[name] = Card(name, sex, id, securityCode);

			m_numOfCards++;

		}

	}
	else
	{

		FILEOPENERROR("data/CardInfo.txt");

	}

}

void DoorManager::CopyFile(std::fstream &file, std::vector<std::string> &lines)
{

	file.seekg(0);

	while (file.good())
	{

		std::string line;

		std::getline(file, line);

		lines.push_back(line);

	}

	file.seekg(0);	

}

void DoorManager::CopyToFile(std::fstream &file, const std::vector<std::string> &lines)
{

	file.seekp(0);

	for (auto const &line : lines)
	{

		file << line << '\n';

	}

}

void DoorManager::CopyCardInfoToFile()
{

	std::fstream file;

	file.open("data/CardInfo.txt", std::ios::out | std::ios::trunc);

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

void DoorManager::SaveNextId()
{

	std::fstream file;

	file.open("data/NextId.txt", std::ios::out);
	
	if (file.is_open())
	{

		file << m_nextId;

	}
	else
	{

		FILEOPENERROR("data/CardInfo/txt");

	}

	file.close();

}

void DoorManager::FILEOPENERROR(const std::string &fileName)
{

	std::cout << "Unable to open file '"  << fileName << "'\n";

}
