#pragma once

#include <string>
#include <vector>

static const std::vector<std::string> WEEKDAYS
{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday", 
	"Thursday",
	"Friday",
	"Saturday"
	
};

class History
{

public:


	History() {}

	History(const std::string &name, int year, int mon, int day, int hour, int min, int sec, int weekDay)
		:	m_name		(name),
			m_year		(std::to_string(year)),
			m_mon		(std::to_string(mon)),
			m_day		(std::to_string(day)),
			m_hour		(std::to_string(hour)),
			m_min		(std::to_string(min)),
			m_sec		(std::to_string(sec)),
			m_weekDay	(WEEKDAYS[weekDay])	
	{


		m_time =  m_day + '/' + m_mon + '/' + m_year + '\t'  + m_hour + "::" + m_min + "::" + m_sec + '\t' + m_weekDay;
	
	}

	const std::string &GetName() const
	{

		return m_name;

	}

	const std::string &GetTime() const
	{

		return m_time;

	}

	const std::string  &GetYear()
	{

		return m_year;

	}

	const std::string &GetMonth()
	{

		return m_mon;

	}

	const std::string &GetDay()
	{

		return m_day;

	}

	const std::string &GetHour()
	{

		return m_hour;

	}

	const std::string &GetMinute()
	{

		return m_min;

	}

	const std::string &GetSecond()
	{

		return m_sec;

	}

	const std::string &GetWeekDay()
	{

		return m_weekDay;

	}

private:

	std::string m_name;
	std::string m_time;

	std::string m_weekDay;
	std::string m_year, m_mon, m_day, m_hour, m_min, m_sec;

};
