/*
    Written by Jtaim
    Date 13 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Drill 5
    This drill simply involves the sequence of versions of Date to work 9.7.4.
    For each version define Date called today initialized to June 25, 1978.
    Then, define a Date called tomorrow and give it a value by coping today into it and increasing its day by using add_day().
    Finally, output today and tomorrow using a << defined as in 9.8.

    Your check for a valid date may be very simple.
    Feel free to ignore leap years.
    However, don't accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range.
    Test each version with at least one invalid date (e.g., 2004,13,-5).
*/

#include"../includes/ppp.h"

enum class Month{
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month operator++(Month& m)
{
    m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
    return m;
}

class Date{
public:
    class Invalid{};                        // to be used as exception
    Date();
    Date(int y, Month m, int d);            // check for valid date and initialize

    Month month() const;
    int day() const;
    int year() const;
    void add_day(const int n);
    void add_month(const int n);
    void add_year(const int n);
    const Date& default_date();
private:
    int m_year;
    Month m_month;
    int m_day;
    bool is_valid();

    const int month_day[12]{31,28,31,30,31,30,31,31,30,31,30,31};
};

Date::Date()
    : m_year{default_date().year()}, m_month{default_date().month()}, m_day{default_date().day()}
{
}

Date::Date(int y, Month m, int d)
    : m_year{y}, m_month{m}, m_day{d}
{
    if(!is_valid()) throw Invalid{};
}

Month Date::month() const
{
    return m_month;
}

int Date::day() const
{
    return m_day;
}

int Date::year() const
{
    return m_year;
}

void Date::add_day(const int n)
{
    // increase dd by n days.
    if(m_day + n <= month_day[(int)m_month - 1]){
        m_day += n;
    }
    else{
        int new_day{m_day + n - month_day[(int)m_month - 1]};
        while(true){
            ++m_month;
            if(m_month == Month::jan){
                ++m_year;
            }
            if(new_day <= month_day[(int)m_month - 1]){
                m_day = new_day;
                break;
            }
            new_day -= month_day[(int)m_month - 1];
        }
    }
}

void Date::add_month(const int n)
{
    for(int i{}; i < n; ++i) ++m_month;
}

void Date::add_year(const int n)
{
    m_year += n;
}

const Date& Date::default_date()
{
    static Date dd{2001, Month::jan, 1};
    return dd;
}

bool Date::is_valid()
{
    if(m_month < Month::jan || m_month > Month::dec) return false;
    if(m_day < 1 || m_day > month_day[(int)m_month - 1]) return false;
    if(m_year <= 0) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    return os << '(' << d.year() << ',' << (int)d.month() << ',' << d.day() << ')';
}

int main()
try{
    try{
        Date today{1978, Month::jun, 25};
        //Date today{2004, 13, -5};
        Date tomorrow = today;
        tomorrow.add_day(1);

        std::cout << "today" << today << '\n';
        std::cout << "tomorrow" << tomorrow << '\n';
    }
    catch(Date::Invalid){
        ppp::error("invalid date");
    }

    ppp::keep_window_open();
    return 0;
}

catch(std::exception& e){
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...){
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}