#pragma once

#include <string>

class History
{

public:

	History() {}

	History(const std::string &name, int year, int mon, int day, int hour, int min, int sec, int weekDay)
		:	m_name		(name),
			m_year		(year),
			m_mon		(mon),
			m_day		(day),
			m_hour		(hour),
			m_min		(min),
			m_sec		(sec),
			m_weekDay	(weekDay)	
	{

		using namespace std;

		m_time = to_string(year) + ' ' + to_string(mon) + ' ' + to_string(day) + ' ' + to_string(hour) + ' ' + to_string(min) + ' ' + to_string(sec) + ' ' + to_string(weekDay);
	
	}

	const std::string GetName() const
	{

		return m_name;

	}

	const std::string GetTime() const
	{

		return m_time;

	}


private:

	std::string m_name;
	std::string m_time;

	int m_year, m_mon, m_day, m_hour, m_min, m_sec, m_weekDay;

};
