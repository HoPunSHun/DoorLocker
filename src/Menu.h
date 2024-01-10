#pragma once

#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <string>

class Menu
{

public:	

	Menu(){}

	Menu(const std::string &name)
		:	m_name	(name)
	{

		std::ifstream file; 	
		file.open("data/Menu/" + name + ".txt");

		if (file.is_open())
		{

			while (file.good())
			{


				std::string line;

				std::getline(file, line);

				line += '\n';

				m_text += line;

			}

		}	

		file.close();
	
	}

	void AddOption(int optionNum, const std::function<void()> &option)
	{

		m_options[optionNum] = option;
	
	}

	void RunOption(int optionNum)
	{

		m_options[optionNum]();

	}

	void PrintMenu()
	{

		std::cout << "\033c";
		std::cout << m_text;

	}

	int GetOptionNum()
	{

		return m_options.size();

	}

	const std::map<int, std::function<void()>> &GetOptions()
	{

		return m_options;

	}

private:

	std::string m_name;

	std::string m_text;

	std::map<int, std::function<void()>> m_options;

};
