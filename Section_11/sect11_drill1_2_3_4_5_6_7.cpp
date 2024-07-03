/*
    Written by Jtaim
    Date 12 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Drill 1
    Start a program called Test_output.cpp. Declare an integer birth_year and assign it the year you were born.

    Section 11 Drill 2
    Output your birth_year in decimal, hexadecimal, and octal form.

    Section 11 Drill 3
    Label each value with the name of the base used.

    Section 11 Drill 4
    Did you line up your output in columns using the tab character? If not, do it.

    Section 11 Drill 5
    Now output your age.

    Section 11 Drill 6
    Was there a problem? What happened? Fix your output to decimal.

    Section 11 Drill 7
    Go back to 2 and cause your output to show the base for each output.
*/

#include "ppp.hpp"
#include <chrono>
#include <print>

int main()
try
{
    int birth_year{ 1970 };

    /*
    std::cout << "The year " << birth_year << " in decimal:\t" << birth_year << '\n'
        << "The year " << birth_year << " in hexadecimal:\t" << std::hex << std::showbase << birth_year << std::dec << '\n'
        << "The year " << birth_year << " in octal:\t\t" << std::oct << std::showbase << birth_year << std::dec << '\n';
    */

    // new in stdc++23 https://en.cppreference.com/w/cpp/io/basic_ostream/print 
    // https://en.cppreference.com/w/cpp/utility/format/spec
    std::print( "The year {1} {0:17}{1}\n", "in decimal:", birth_year );
    std::print( "The year {1} {0:17}{1:#0x}\n", "in hexadecimal:", birth_year );
    std::print( "The year {1} {0:17}{1:#0o}\n", "in octal:", birth_year );
    std::print( "The year {1} {0:17}{1:#0b}\n", "in binary:", birth_year );

    const auto now = std::chrono::system_clock::now();
    const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>( now ) };

    //std::cout << "My age is " << static_cast<int>( ymd.year() ) - birth_year << "\n";
    std::print( "My age is {}\n", static_cast<int>( ymd.year() ) - birth_year );

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
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
