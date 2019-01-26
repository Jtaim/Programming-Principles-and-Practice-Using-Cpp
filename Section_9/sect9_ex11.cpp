/*
    Written by Jtaim
    Date 23 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 11
    this is the test program.
    Add helper functions to Date class in Chrono namespace
    - next_workday() any day that is not Saturday or Sunday is a workday
    - week_of_year() week 1 is the week with January 1 and first day of week is Sunday
*/

#include"../includes/ppp.h"

#include "Chrono.h"

int main()
try{
    Chrono::Date d1{2019,Chrono::Month::jan, 18};

    std::cout << d1 << " Week#: " << week_of_year(d1) << '\n';

    auto n_wday{Chrono::next_workday(d1)};

    std::cout << n_wday << " Week#: " << week_of_year(n_wday) << '\n';
    
    n_wday = Chrono::next_sunday(n_wday);

    std::cout << n_wday << " Week#: " << week_of_year(n_wday) << '\n';

    n_wday.add_year(1);
    n_wday.add_month(1);
    n_wday.add_day(2);

    std::cout << n_wday << " Week#: " << week_of_year(n_wday) << '\n';

    n_wday.add_year(1);

    std::cout << n_wday << " Week#: " << week_of_year(n_wday) << '\n';

    n_wday.add_month(10);

    std::cout << n_wday << " Week#: " << week_of_year(n_wday) << '\n';

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