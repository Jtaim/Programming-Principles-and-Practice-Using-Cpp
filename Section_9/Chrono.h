// file Chrono.h

#pragma once

#include <array>
#include <chrono>
#include <ctime>
#include <iostream>

namespace Chrono
{

	enum class Month
	{
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	enum class Day
	{
		sun, mon, tue, wed, thu, fri, sat
	};

	const std::array<int, 12> month_day{31,28,31,30,31,30,31,31,30,31,30,31};

	class Date
	{
	public:
		class Invalid {};    // to throw exceptions
		Date();             // default constructor
		Date(int y, Month m, int d);

		// the default copy operation is fine

		// non-modifying operations:
		int get_day() const { return m_day; }
		Month get_month() const { return m_month; }
		int get_year() const { return m_year; }

		// modifying operations
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);

		// helper functions
		friend bool operator==(const Date& a, const Date& b);
		friend bool operator!=(const Date& a, const Date& b);
		friend bool operator>(const Date& a, const Date& b);
		friend bool operator<(const Date& a, const Date& b);
		friend bool operator>=(const Date& a, const Date& b);
		friend bool operator<=(const Date& a, const Date& b);
		friend std::ostream& operator<<(std::ostream& os, const Date& d);
		friend std::istream& operator>>(std::istream& is, Date& dd);

	private:
		long m_days; // zero = Jan 1, 1970
		int m_year;
		Month m_month;
		int m_day;

		void days_from_zero();

		std::tm dz{0,0,0,1,0,(1970 - 1900)};
		std::time_t day_zero = std::mktime(&dz);
	};

	// helper functions
	bool is_date(int y, Month m, int d);    // true for valid date
	bool leap_year(int y);                  // true if is a leap year

	Day day_of_week(const Date& d);     // day of week of d
	Date next_sunday(const Date& d);    // next Sunday after d
	Date next_weekday(const Date& d);   // next weekday after d
	Date next_workday(const Date& d);   // return next work day (mon - fri)
	int week_of_year(const Date& d);    // return week number

}   // Chrono
