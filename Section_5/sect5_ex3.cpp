//written by Jtaim
//date 5 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 3
Celsius to Kelvin converter
throws error in main if input is below absolute 0
*/
#include "section5.h"

double ctok(const double c)	// converts Celsius to Kelvin
{
	double celsiusToKelvin = c + 273.15;
	return celsiusToKelvin;
}

int main()
try
{
	std::cout << "Enter a temperature in Celsius to covert to Kelvin:\n";
	double celsius{ 0.0 }; //input variable
	std::cin >> celsius;
	if (celsius < -273.15)
	{
		error("Can not be below absolute zero!\n");
	}
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
