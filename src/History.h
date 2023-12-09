#pragma once

#include <string>

class History
{

public:

	History() {}

	History(const std::string &cardName, int time_h, int time_m)
		:	m_name		(cardName),
			m_time_h	(time_h),
			m_time_m	(time_m)
	{}

	
	History(int time_h, int time_m)
		:	m_name		("Password"),
			m_time_h	(time_h),
			m_time_m	(time_m)
	{}
	
	const std::string GetName() const
	{

		return m_name;

	}	

	const std::string GetTime() const
	{

		return (std::to_string(m_time_h) + ':' + std::to_string(m_time_m));

	}

	int GetHour() const
	{

		return m_time_h;

	}

	int GetMinute() const
	{

		return m_time_m;

	}

private:

	int m_time_h;
	int m_time_m;

	std::string m_name;

};
