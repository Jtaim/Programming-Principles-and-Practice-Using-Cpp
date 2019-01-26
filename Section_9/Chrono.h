// file Chrono.h

#pragma once

#include <iostream>
#include <array>

namespace Chrono
{

    enum class Month{
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    enum class Day{
        sun, mon, tue, wed, thu, fri, sat
    };

    const std::array<int, 12> month_day{31,28,31,30,31,30,31,31,30,31,30,31};

    class Date{
    public:
        Date();     // default constructor
        Date(int y, Month m, int d);    // check for valid date and initialize

        // the default copy operation is fine

        // non-modifying operations:
        int day() const { return m_day; }
        Month month() const { return m_month; }
        int year() const { return m_year; }

        // modifying operations
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
        
    private:
        int m_year;
        Month m_month;
        int m_day;
    };

    // helper functions
    bool is_date(int y, Month m, int d);    // true for valid date
    bool leap_year(int y);                  // true if is a leap year

    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);
    bool operator>(const Date& a, const Date& b);
    bool operator<(const Date& a, const Date& b);
    bool operator>=(const Date& a, const Date& b);
    bool operator<=(const Date& a, const Date& b);

    std::ostream& operator<<(std::ostream& os, const Date& d);
    std::istream& operator>>(std::istream& is, Date& dd);

    Day day_of_week(const Date& d);     // day of week of d
    Date next_sunday(const Date& d);    // next Sunday after d
    Date next_weekday(const Date& d);   // next weekday after d
    Date next_workday(const Date& d);   // return next work day (mon - fri)
    int week_of_year(const Date& d);    // return week number

}   // Chrono
