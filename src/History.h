#pragma once

#include <string>

class History
{

public:

	History() {}

	History(const std::string &cardName, int time_h, int time_m)
		:	m_type		("Card"),
			m_cardName	(cardName),
			m_time_h	(time_h),
			m_time_m	(time_m)
	{}

	
	History(int time_h, int time_m)
		:	m_type		("Password"),	
			m_time_h	(time_h),
			m_time_m	(time_m)
	{}
	
	const std::string GetType() const
	{

		return m_type;

	}

	const std::string GetCardName() const
	{

		return m_cardName;

	}	

	const std::string GetTime() const
	{

		return (std::to_string(m_time_h) + ':' + std::to_string(m_time_m));

	}

private:

	std::string m_type;

	int m_time_h;
	int m_time_m;

	std::string m_cardName = "NoCard";

};
