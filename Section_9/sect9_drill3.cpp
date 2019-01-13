/*
    Written by Jtaim
    Date 13 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Drill 3
    This drill simply involves the sequence of versions of Date to work 9.4.3.
    For each version define Date called today initialized to June 25, 1978.
    Then, define a Date called tomorrow and give it a value by coping today into it and increasing its day by using add_day().
    Finally, output today and tomorrow using a << defined as in 9.8.

    Your check for a valid date may be very simple.
    Feel free to ignore leap years.
    However, don't accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range.
    Test each version with at least one invalid date (e.g., 2004,13,-5).
*/

#include"../includes/ppp.h"

class Date{
public:
    Date(int y, int m, int d);
    void add_day(const int n);
    int month() const { return m_month; }
    int day() const { return m_day; }
    int year() const { return m_year; }

private:
    int m_year;
    int m_month;
    int m_day;

    const int month_day[12]{31,28,31,30,31,30,31,31,30,31,30,31};
};

Date::Date(int y, int m, int d)
{
    // check that (y,m,d) is a valid date.
    if(m < 1 || m > 12) ppp::error("Invalid month!");
    if(d < 1 || d > month_day[m - 1]) ppp::error("Invalid day!");
    if(y < 0) ppp::error("Invalid year!");
    m_month = m;
    m_day = d;
    m_year = y;
}

void Date::add_day(const int n)
{
    // increase dd by n days.
    if(m_day + n <= month_day[m_month - 1]){
        m_day += n;
    }
    else{
        int new_day{m_day + n - month_day[m_month - 1]};
        while(true){
            ++m_month;
            if(m_month > 12){
                m_month = 1;
                ++m_year;
            }
            if(new_day <= month_day[m_month - 1]){
                m_day = new_day;
                break;
            }
            new_day -= month_day[m_month - 1];
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

int main()
try{
    Date today{1978, 6, 25};
    //Date today{2004, 13, -5};
    Date tomorrow = today;
    tomorrow.add_day(1);

    std::cout << "today" << today << '\n';
    std::cout << "tomorrow" << tomorrow << '\n';

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