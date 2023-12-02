#include "DoorManager.h"

#include <iostream>
#include <fstream>

void DoorManager::Init()
{

	ReadCardInfo();

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

			file >> sex >> id;	

			m_cards.push_back(Card(name, sex, id));

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

		std::cout << i + 1 << '.' << card.GetName() << ' ' << card.GetSex() << ' ' << card.GetId() << '\n';

	}

}

void DoorManager::FILEOPENERROR(const char* fileName)
{

	std::cout << "Unable to open file '"  << fileName << "'\n";

}
