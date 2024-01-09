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

	void AddOption(const std::function<void()> &option)
	{

		m_options.push_back(option);	
	
	}

	void RunOption(int optionNum)
	{

		m_options[optionNum]();

	}

	void PrintMenu()
	{

		std::cout << m_text;

	}

	int GetOptionNum()
	{

		return m_options.size();

	}

private:

	std::string m_name;

	std::string m_text;

	std::vector<std::function<void()>> m_options;

};
