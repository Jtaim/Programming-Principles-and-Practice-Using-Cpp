//written by Jtaim
//date 5 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 3
Celsius to Kelvin converter
throws error in main if input is below absolute 0
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
    if (celsius < -273.15) {
        error("Can not be below absolute zero!\n");
    }
    double kelvin = ctok(celsius);
    std::cout << kelvin << std::endl;

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
