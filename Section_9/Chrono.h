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
        class Invalid{};    // to throw exceptions
        Date();             // default constructor
        Date(int y, Month m, int d);
        //Date(long int d);

        // the default copy operation is fine

        // non-modifying operations:
        int get_day() const { return m_day; }
        Month get_month() const { return m_month; }
        int get_year() const { return m_year; }
        long int get_date() const { return m_date; }

        // modifying operations
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

        static constexpr int zero_year{1970};
        static constexpr Month zero_month{Month::jan};
        static constexpr int zero_day{1};
        static constexpr long zero_date{0L};

        static constexpr int year_size{365};
        static constexpr int leap_year_size{366};

    private:
        long int m_date; // zero = Jan 1, 1970
        int m_year;
        Month m_month;
        int m_day;

        //void days_from_zero();
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
