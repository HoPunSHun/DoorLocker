#include "DoorManager.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>

DoorManager::DoorManager()
	:	m_nextId	(0)
{}

void DoorManager::Init()
{

	ReadCardInfo();

	std::cout << CheckCard("data/JeremyCard.txt") << '\n';

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

			m_cards.push_back(Card(name, sex, id, securityCode));

			m_numOfCards++;

		}

	}
	else
	{

		FILEOPENERROR("data/CardInfo.txt");

	}

}

void DoorManager::ListCards()
{

	for (int i = 0; i < m_cards.size(); i++)
	{

		Card card = m_cards[i];

		std::cout << i + 1 << '.' << card.GetName() << ' ' << card.GetSex() << ' ' << card.GetId() << ' ' << card.GetSecurityCode() << '\n';

	}

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

void DoorManager::AddCard(const std::string &name, int sex, int securityCodeLevel)
{

	std::string securityCode = GenerateSecurityCode(securityCodeLevel);

	Card card(name, sex, m_nextId, GenerateSecurityCode(securityCodeLevel));	

	m_cards.push_back(card);

	std::fstream file;

	file.open("data/CardInfo.txt", std::ios::in | std::ios::app);

	file << '\n' << name << ' ' << sex << ' ' << securityCode;

	m_nextId++;

	SaveNextId();

}

bool DoorManager::CheckCard(const std::string& cardPath)
{

	Card card;

	ReadCardInfo(cardPath, card);

	for (auto _card : m_cards)
	{

		if (card == _card)
		{

			return true;

		}

	}

	return false;

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

void DoorManager::FILEOPENERROR(const std::string &fileName)
{

	std::cout << "Unable to open file '"  << fileName << "'\n";

}
