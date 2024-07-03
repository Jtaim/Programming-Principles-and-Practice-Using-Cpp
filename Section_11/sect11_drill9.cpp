/*
    Written by Jtaim
    Date 12 Jan 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Drill 9
    Write some code to print the number 1234567.89 three times, first using default float, then fixed, then scientific forms.
    Which output form presents the user with the most accurate representation?
    Explain why.
*/

#include "ppp.hpp"
#include <print>

int main()
try
{
    double number{ 123456.8923 };

    /*
    std::cout << "The number in default: " << number << "\n"
        << "The number in fixed: " << std::fixed << number << "\n"
        << "The number in scientific: " << std::scientific << number << "\n"
        << "The number in default: " << std::defaultfloat << number << "\n\n";
    */

    // fixed seems to present the number more accurately.

    std::print( "{:25} = {}\n", "The number in default", number );         // default allowed by type and hides trailing decimal zeros
    std::print( "{:25} = {:f}\n", "The number in fixed", number );         // default precision of 6
    std::print( "{:25} = {:e}\n", "The number in scientific", number );    // default precision of 6
    std::print( "{:25} = {:.8g}\n", "The number in general", number );     // default precision of 6, but I set to 8

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
