//Chrono.cpp
#include "Chrono.h"

namespace Chrono
{
    // member function definitions
    Date::Date(int y, Month m, int d)
        : m_year{y}, m_month{m}, m_day{d}
    {
        if(!is_date(y, m, d)) throw std::runtime_error("Invalid Date!");
    }

    Date default_date()
    {
        static const Date dd{2001, Month::jan, 1};    // start of 21st century
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
        if(n < 0) throw std::runtime_error("can't add negative days!");
        int days = m_day + n; // get new unchecked day number
        int dm(month_day.at((int)m_month - 1));
        while(days > dm){
            switch(m_month){
                case Month::feb:
                    //29 days feb leap year
                    if(leap_year(m_year)){
                        if(days <= dm + 1){
                            m_day = days;
                            days = 0;
                        }
                        else{
                            add_month(1);
                            days -= (dm + 1);
                        }
                    }
                    else{
                        add_month(1);
                        days -= dm;
                    }
                    break;
                case Month::dec:
                    add_month(1);
                    ++m_year;
                    days -= dm;
                    break;
                default:
                    days -= dm;
                    add_month(1);
                    break;
            }
            dm = month_day.at((int)m_month - 1);
        }
        if(days < 0) throw std::runtime_error("days can't be negative!");
        if(days > 0) m_day = days; // if 0 then used by leap year
    }

    // add month will clamp to last day to the n month
    void Date::add_month(const int n)
    {
        if(n < 0) throw std::runtime_error("can't add negative months!");
        int day = m_day;
        int months = n;
        if(n >= 12 && n != 0){
            add_year(static_cast<int>(n % 12));
            months -= (n % 12) * 12;
        }
        if((int)m_month + months > 12){
            add_year(1);
            m_month = Month((int)m_month + months - 12);
        }
        else{
            m_month = Month((int)m_month + months);
        }
        if(day > month_day.at((int)m_month + 1)){
            if(m_month == Month::feb && !leap_year(m_year)){
                m_day = 29;
            }
            m_day = month_day.at((int)m_month + 1);
        }
        else{
            m_day = day;
        }
    }

    void Date::add_year(const int n)
    {
        // beware of leap years
        if(m_month == Month::feb && m_day == 29 && !leap_year(m_year + n)){
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

    bool operator>(const Date& a, const Date& b)
    {
        if(a.year() > b.year()) return true;
        if(a.year() == b.year() && a.month() > b.month()) return true;
        if(a.year() == b.year() && a.month() == b.month() && a.day() > b.day()) return true;
        return false;
    }

    bool operator<(const Date& a, const Date & b)
    {
        if(a.year() < b.year()) return true;
        if(a.year() == b.year() && a.month() < b.month()) return true;
        if(a.year() == b.year() && a.month() == b.month() && a.day() < b.day()) return true;
        return false;
    }

    bool operator>=(const Date& a, const Date & b)
    {
        return (a == b || a > b);
    }

    bool operator<=(const Date& a, const Date & b)
    {
        return (a == b || a < b);
    }

    std::ostream& operator<<(std::ostream& os, const Date& d)
    {
        return
            os << '(' << d.year()
            << ',' << (int)d.month()
            << ',' << d.day() << ')';
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
        static const std::array<int, 12> t{0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

        if(d.month() < Month::mar){
            --y;
        }
        return Day((y + y / 4 - y / 100 + y / 400 + t.at(m - 1) + d.day()) % 7);
    }

    Date next_sunday(const Date& d)
    {
        Date date_now{d};
        Day day_now{day_of_week(d)};
        date_now.add_day(7 - (int)day_now);
        return date_now;
    }

    Date next_weekday(const Date& d)
    {
        Date date_now{d};
        date_now.add_day(1);
        return date_now;
    }

    Date next_workday(const Date& d)
    {
        Date nwd{d};
        // check if weekend
        auto day{day_of_week(d)};
        switch(day){
            case Day::fri:
                nwd.add_day(3);
                break;
            case Day::sat:
                nwd.add_day(2);
                break;
            default:
                nwd.add_day(1);
                break;
        }
        return nwd;
    }

    int week_of_year(const Date& d)
    {
        Date date{d.year(), Month::jan, 1};
        int week_number{};
        while(d >= date){
            ++week_number;
            date = next_sunday(date);
        }
        return week_number;
    }

}   // Chrono