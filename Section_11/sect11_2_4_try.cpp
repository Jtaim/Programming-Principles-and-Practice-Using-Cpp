/*
    Written by Jtaim
    Date 7 June 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Write some code to print the number 1234567.89 three times, first using defaultfloat, then fixed, then scientific.
    Which output form presents the user with the most accurate representation? Explain why.
*/

#include <ppp.hpp>

int main()
{
    constexpr double df{ 1234567.89 };

    std::cout << df << "\t"
        << std::fixed << df << "\t\t"
        << std::scientific << df << "\n";
    std::cout << std::defaultfloat << std::setprecision(5)
        << df << "\t"
        << std::fixed << df << "\t\t"
        << std::scientific << df << "\n";
    std::cout << std::defaultfloat << std::setprecision( 8 )
        << df << "\t"
        << std::fixed << df << "\t"
        << std::scientific << df << "\n";

    ppp::keep_window_open();
    return 0;
}
