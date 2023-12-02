#pragma once

#include <string>

class Card
{

public:

	Card(){}

	Card(const std::string &name, int sex, int id)
		:	m_name	(name),
			m_sex	(sex),
			m_id	(id)
	{}

	const std::string &GetName()
	{

		return m_name;

	}

	int GetSex()
	{

		return m_sex;

	}

	int GetId()
	{

		return m_id;

	}

private:

	std::string m_name;
	int m_sex;

	int m_id;

};
