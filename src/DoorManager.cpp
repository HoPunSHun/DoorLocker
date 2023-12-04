#include "DoorManager.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>

DoorManager::DoorManager()
{}

void DoorManager::Init()
{

	ReadNextId();
	ReadCardInfo();

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

			int sex;
			int id;

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

		std::cout << i + 1 << '.' << card.GetName() << ' ' << card.GetSex() << ' ' << card.GetId() << card.GetSecurityCode() << '\n';

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

	Card card(name, sex, m_nextId, GenerateSecurityCode(securityCodeLevel));	

	m_nextId++;

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

void DoorManager::FILEOPENERROR(const char* fileName)
{

	std::cout << "Unable to open file '"  << fileName << "'\n";

}
