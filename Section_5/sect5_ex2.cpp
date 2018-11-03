//written by Jtaim
//date 4 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 2
find errors and document
*/
#include "section5.h"

double ctok(double c)	// converts Celsius to Kelvin
{
    //int k = c + 273.15;
    //use double prevent narrow errors
    //use descriptive variable names
    double celsiusToKelvin = c + 273.15;
    //return int;
    //compile error: type name is not allowed
    return celsiusToKelvin;
}

int main()
{
    double celsius{ 0.0 }; //input variable
    //cin >> d;
    //compile error: identifier "d" is undefined
    std::cin >> celsius;
    //double k = ctok("c");
    //compile error: argument error
    double kelvin = ctok(celsius);
    //Cout << k << '\n';
    //compile error: identifier "Cout" is undefined
    std::cout << kelvin << '\n';

    keep_window_open();
    return 0;
}
