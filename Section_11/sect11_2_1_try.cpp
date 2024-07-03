/*
    Written by Jtaim
    Date 7 June 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Output your birth year in decimal, hexadecimal, and octal form. Label each value.
    Line up your output in columns using the tab character. Now output your age.
*/

#include <ppp.hpp>
#include <chrono>

constexpr std::chrono::year birth_year{ 1970 };

int main()
{

    std::cout << "Birth Year ";
    std::cout << "\tDec: " << birth_year;
    std::cout << "\tHex: " << std::hex << birth_year;
    std::cout << "\tOct: " << std::oct << birth_year << "\n";

    const auto now = std::chrono::system_clock::now();
    const std::chrono::year_month_day ymd{ std::chrono::floor<std::chrono::days>( now ) };
    const auto age{ static_cast<int>(ymd.year()) - static_cast<int>( birth_year) };

    std::cout << "Age";
    std::cout << "\t\tDec: " << std::dec << age;
    std::cout << "\t\tHex: " << std::hex << age;
    std::cout << "\t\tOct: " << std::oct << age << std::endl;

    ppp::keep_window_open();
    return 0;
}