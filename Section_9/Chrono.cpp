//Chrono.cpp
#include "Chrono.hpp"

namespace Chrono
{
    // member function definitions
    Date::Date( int y, Month m, int d )
        : m_year{ y }, m_month{ m }, m_day{ d }
    {
        if( !is_date( y, m, d ) ) throw std::runtime_error( "Invalid Date!" );
        days_from_zero();
    }

    Date default_date()
    {
        static const Date dd{ 2001, Month::JAN, 1 };    // start of 21st century
        return dd;
    }

    Date::Date()
        : m_year{ default_date().get_year() },
        m_month{ default_date().get_month() },
        m_day{ default_date().get_day() }
    {
        days_from_zero();
    }

    void Date::add_day( const int n )
    {
        if( n < 0 ) throw std::runtime_error( "can't add negative days!" );
        if( n > 0 )
        {
            for( int i{ 1 }; i <= n; ++i )
            {
                int t = m_day + 1;
                switch( m_month )
                {
                    case Chrono::Month::FEB:
                        if( t <= ( leap_year( m_year ) ? 29 : 28 ) )
                        {
                            m_day = t;
                        }
                        else
                        {
                            m_month = Month::MAR;
                            m_day = 1;
                        }
                        break;
                    case Chrono::Month::DEC:
                        if( t <= 31 )
                        {
                            m_day = t;
                        }
                        else
                        {
                            m_month = Month::JAN;
                            m_day = 1;
                            ++m_year;
                        }
                        break;
                    default:
                        if( t <= month_day.at( (int)m_month - 1 ) )
                        {
                            m_day = t;
                        }
                        else
                        {
                            m_month = Month( (int)m_month + 1 );
                            m_day = 1;
                        }
                        break;
                }
            }
            days_from_zero();
        }
    }

    // add month will clamp to last day to the n month
    void Date::add_month( const int n )
    {
        if( n < 0 ) throw std::runtime_error( "can't add negative months!" );
        if( n > 0 )
        {
            int months = n;
            int years{}; // keeps track of overlapped years and add in after adding all the months
            if( n >= 12 && n != 0 )
            {
                int add_months{ n % 12 };
                years = add_months;
                months -= add_months * 12;
            }
            if( (int)m_month + months > 12 )
            {
                m_month = Month( (int)m_month + months - 12 );
                years += 1;
            }
            else
            {
                m_month = Month( (int)m_month + months );
            }
            //clip to last day of month if previous was more days
            if( m_day > month_day.at( (int)m_month - 1 ) )
            {
                if( m_month == Month::FEB && !leap_year( m_year ) )
                {
                    m_day = 29;
                }
                m_day = month_day.at( (int)m_month - 1 );
            }
            days_from_zero();
            add_year( years );
        }
    }

    void Date::add_year( const int n )
    {
        if( n < 0 ) throw std::runtime_error( "can't add negative years!" );
        if( n > 0 )
        {
            // beware of leap years
            if( m_month == Month::FEB && m_day == 29 && !leap_year( m_year + n ) )
            {
                // use March 1 instead of February 29
                m_month = Month::MAR;
                m_day = 1;
            }
            m_year += n;
            days_from_zero();
        }
    }

    void Date::days_from_zero()
    {
        std::tm now{};
        now.tm_mday = m_day;
        now.tm_mon = (int)m_month - 1;
        now.tm_year = m_year - 1900;

        std::time_t today = std::mktime( &now );
        auto n = std::chrono::system_clock::from_time_t( day_zero );
        auto t = std::chrono::system_clock::from_time_t( today );
        m_days = std::chrono::duration_cast<std::chrono::hours>( t - n ).count() / 24;
    }

    // helper functions

    bool is_date( int y, Month m, int d )
    {
        // assume year is valid
        if( d <= 0 ) return false;    // day must be positive
        if( m < Month::JAN || Month::DEC < m ) return false;

        int days_in_month{ 31 };      // most months have 31 days

        switch( m )
        {
            case Month::FEB:        // the length of February varies
                days_in_month = ( leap_year( y ) ) ? 29 : 28;
                break;
            case Month::APR:
            case Month::JUN:
            case Month::SEP:
            case Month::NOV:
                days_in_month = 30; // rest have 30 days
                break;
        }

        if( days_in_month < d ) return false;

        return true;
    }

    /*
        formula for calculating leap years for the Gregorian calender:
        - The year is evenly divisible by 4;
        - If the year can be evenly divided by 100, it is NOT a leap year, unless;
        - The year is also evenly divisible by 400: Then it is a leap year.
    */
    bool leap_year( int y )
    {
        if( !( y % 400 ) )
        {
            return true;
        }
        if( y % 100 && !( y % 4 ) )
        {
            return true;
        }
        return false;
    }

    bool operator==( const Date& a, const Date& b )
    {
        return a.m_days == b.m_days;
    }

    bool operator!=( const Date& a, const Date& b )
    {
        return !( a == b );
    }

    bool operator>( const Date& a, const Date& b )
    {
        return a.m_days > b.m_days;
    }

    bool operator<( const Date& a, const Date& b )
    {
        return a.m_days < b.m_days;
    }

    bool operator>=( const Date& a, const Date& b )
    {
        return a > b || a == b;
    }

    bool operator<=( const Date& a, const Date& b )
    {
        return a < b || a == b;
    }

    std::ostream& operator<<( std::ostream& os, const Date& d )
    {
        return
            os << '(' << d.m_year
            << ',' << (int)d.m_month
            << ',' << d.m_day << ')';
    }

    std::istream& operator>>( std::istream& is, Date& dd )
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if( !is ) return is;
        // check for format error
        if( ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')' )
        {
            is.clear( std::ios_base::failbit );   // set the fail bit
            return is;
        }

        dd.m_year = y;
        dd.m_month = Month( m );
        dd.m_day = d;
        return is;
    }

    Day day_of_week( const Date& d )
    {
        // good for any Gregorian date
        int y{ d.get_year() };
        int m{ static_cast<int>( d.get_month() ) };
        static const std::array<int, 12> t{ 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

        if( d.get_month() < Month::MAR )
        {
            --y;
        }
        return Day( ( y + y / 4 - y / 100 + y / 400 + t.at( m - 1 ) + d.get_day() ) % 7 );
    }

    Date next_sunday( const Date& d )
    {
        Date date_now{ d };
        Day day_now{ day_of_week( d ) };
        date_now.add_day( 7 - (int)day_now );
        return date_now;
    }

    Date next_weekday( const Date& d )
    {
        Date date_now{ d };
        date_now.add_day( 1 );
        return date_now;
    }

    Date next_workday( const Date& d )
    {
        Date nwd{ d };
        // check if weekend
        auto day{ day_of_week( d ) };
        switch( day )
        {
            case Day::FRI:
                nwd.add_day( 3 );
                break;
            case Day::SAT:
                nwd.add_day( 2 );
                break;
            default:
                nwd.add_day( 1 );
                break;
        }
        return nwd;
    }

    int week_of_year( const Date& d )
    {
        Date date{ d.get_year(), Month::JAN, 1 };
        int week_number{};
        while( d >= date )
        {
            date = next_sunday( date );
            if( date.get_year() == d.get_year() )
            {
                ++week_number;
            }
            else if( date.get_day() != 1 )
            {
                week_number = 1;
            }
        }
        return week_number;
    }

}   // Chrono