/*
    Written by Jtaim
    Date 13 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Drill 4
    This drill simply involves the sequence of versions of Date to work 9.7.1.
    For each version define Date called today initialized to June 25, 1978.
    Then, define a Date called tomorrow and give it a value by coping today into it and increasing its day by using add_day().
    Finally, output today and tomorrow using a << defined as in 9.8.

    Your check for a valid date may be very simple.
    Feel free to ignore leap years.
    However, don't accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range.
    Test each version with at least one invalid date (e.g., 2004,13,-5).
*/

#include"../includes/ppp.hpp"

enum class Month
{
    JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC
};

Month operator++( Month& m )
{
    m = ( m == Month::DEC ) ? Month::JAN : Month( int( m ) + 1 );
    return m;
}

class Year
{
public:
    static constexpr int year_min{ 1800 };
    static constexpr int year_max{ 2200 };

    class Invalid {};
    Year( int x ) : y( x ) { if( x < year_min || year_max <= x ) throw Invalid(); }
    int year() { return y; }
private:
    int y{};
};

Year operator++( Year& y )
{
    y = ( y.year() == Year::year_max ) ? y.year() + 1 : throw Year::Invalid();
    return y;
}

class Date
{
public:
    class Invalid {};                        // to be used as exception
    Date( Year y, Month m, int d );	         // check for valid date and initialize
    void add_day( const int n );
    Month month() const { return m_month; }
    int day() const { return m_day; }
    Year year() const { return m_year; }

private:
    Year m_year;
    Month m_month;
    int m_day{};
    bool is_valid();

    static constexpr std::array<int, 12> month_day{ 31,28,31,30,31,30,31,31,30,31,30,31 };
};

Date::Date( Year y, Month m, int d )
    : m_year{ y }, m_month{ m }, m_day{ d }
{
    if( !is_valid() ) throw Invalid{};
}

void Date::add_day( const int n )
{
    // increase dd by n days.
    if( m_day + n <= month_day.at( (int)m_month - 1 ) )
    {
        m_day += n;
    }
    else
    {
        int new_day{ m_day + n - month_day.at( (int)m_month - 1 ) };
        while( true )
        {
            ++m_month;
            if( m_month == Month::JAN )
            {
                ++m_year;
            }
            if( new_day <= month_day.at( (int)m_month - 1 ) )
            {
                m_day = new_day;
                break;
            }
            new_day -= month_day.at( (int)m_month - 1 );
        }
    }
}

bool Date::is_valid()
{
    if( m_month < Month::JAN || m_month > Month::DEC )
    {
        return false;
    }
    if( m_day < 1 || m_day > month_day.at( (int)m_month - 1 ) )
    {
        return false;
    }
    return true;
}

std::ostream& operator<<( std::ostream& os, const Date& d )
{
    return os << '(' << d.year().year() << ',' << (int)d.month() << ',' << d.day() << ')';
}

int main()
try
{
    try
    {
        Date today{ 1978, Month::JUN, 25 };
        //Date today{2004, 13, -5};
        Date tomorrow{ today };
        tomorrow.add_day( 1 );

        std::cout << "today" << today << '\n';
        std::cout << "tomorrow" << tomorrow << '\n';
    }
    catch( Date::Invalid )
    {
        ppp::error( "invalid date" );
    }

    ppp::keep_window_open();
    return 0;
}

catch( std::exception& e )
{
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}
