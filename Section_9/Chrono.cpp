//Chrono.cpp
#include "Chrono.h"

namespace Chrono
{
    // member function definitions
    Date::Date(int y, Month m, int d)
        : m_year{y}, m_month{m}, m_day{d}
    {
        if(!is_date(y, m, d)) throw Invalid{};
    }

    const Date& default_date()
    {
        static Date dd{2001, Month::jan, 1};    // start of 21st century
        return dd;
    }

    Date::Date()
        : m_year{default_date().year()},
        m_month{default_date().month()},
        m_day{default_date().day()}
    {
    }

    void Date::add_day(const int n)
    {
        // TODO
    }

    void Date::add_month(const int n)
    {
        // TODO
    }

    void Date::add_year(const int n)
    {
        // beware of leap years
        if(m_month == Month::feb&&m_day == 29 && !leap_year(m_year + n)){
            // use March 1 instead of February 29
            m_month = Month::mar;
            m_day = 1;
        }
        m_year += n;
    }

    // helper functions

    bool is_date(int y, Month m, int d)
    {
        // assume year is valid
        if(d <= 0) return false;    // day must be positive
        if(m < Month::jan || Month::dec < m) return false;

        int days_in_month{31};      // most months have 31 days

        switch(m){
            case Month::feb:        // the length of February varies
                days_in_month = (leap_year(y)) ? 29 : 28;
                break;
            case Month::apr:
            case Month::jun:
            case Month::sep:
            case Month::nov:
                days_in_month = 30; // rest have 30 days
                break;
        }

        if(days_in_month < d) return false;

        return true;
    }

    /*
        formula for calculating leap years for the Gregorian calender:
        - The year is evenly divisible by 4;
        - If the year can be evenly divided by 100, it is NOT a leap year, unless;
        - The year is also evenly divisible by 400: Then it is a leap year.
    */
    bool leap_year(int y)
    {
        if(!(y % 400)){
            return true;
        }
        if(y % 100 && !(y % 4)){
            return true;
        }
        return false;
    }

    bool operator==(const Date& a, const Date& b)
    {
        return
            a.year() == b.year() &&
            a.month() == b.month() &&
            a.day() == b.day();
    }

    bool operator!=(const Date& a, const Date& b)
    {
        return !(a == b);
    }

    std::ostream& operator<<(std::ostream& os, const Date& d)
    {
        return
            os << '(' << d.year()
            << ',' << (int)d.month()
            << ',' << d.year() << ')';
    }

    std::istream& operator>>(std::istream& is, Date& dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if(!is) return is;
        // check for format error
        if(ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')'){
            is.clear(std::ios_base::failbit);   // set the fail bit
            return is;
        }

        dd = Date(y, Month(m), d);  // update dd
        return is;
    }

    Day day_of_week(const Date& d)
    {
        // good for any Gregorian date
        int y{d.year()};
        int m{static_cast<int>(d.month())};
        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

        if(d.month() < Chrono::Month::mar){
            --y;
        }
        return Day((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d.day()) % 7);
    }

    Date next_Sunday(const Date& d)
    {
        // TODO
        return Date();
    }

    Date next_weekday(const Date& d)
    {
        // TODO
        return Date();
    }

}   // Chrono