//written by Jtaim
//date 4 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 2
find errors and document
*/

#include "section5.h"

// converts Celsius to Kelvin
double ctok(double c)
{
    constexpr double conversion_constant = 273.15;

    double celsiusToKelvin = c + conversion_constant;

    return celsiusToKelvin;
}

int main()
try
{
    std::cout << "Enter a temperature in Celsius to covert to Kelvin:\n";
    double celsius{};
    std::cin >> celsius;
    double kelvin = ctok(celsius);
    std::cout << kelvin << '\n';

    keep_window_open();
    return 0;
}

catch (std::exception& e)
{
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}
