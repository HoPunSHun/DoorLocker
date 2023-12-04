#pragma once

#include <string>

class Card
{

public:

	Card(){}

	Card(const std::string &name, int sex, int id, const std::string &securityCode)
		:	m_name		(name),
			m_sex		(sex),
			m_id		(id),
			m_securityCode	(securityCode)
	{}

	const std::string &GetName() const
	{

		return m_name;

	}

	int GetSex() const
	{

		return m_sex;

	}

	int GetId() const
	{

		return m_id;

	}

	const std::string &GetSecurityCode() const
	{

		return m_securityCode;

	}

private:

	std::string m_name;
	std::string m_securityCode;
	int m_sex;

	int m_id;

};
