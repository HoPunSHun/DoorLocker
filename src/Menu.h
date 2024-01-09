#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>

class Menu
{

public:	

	Menu(){}

	Menu(const std::string &name)
		:	m_name	(name)
	{}

	void AddOption(const std::function<void()> &option)
	{

		m_options.push_back(option);	
	
	}

	void RunOption(int optionNum)
	{

		m_options[optionNum]();

	}

private:

	std::string m_name;

	std::vector<std::function<void()>> m_options;

};
