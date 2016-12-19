//written by Jtaim
//date 1 Nov 2015
//updated 18 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 4
Celsius to Kelvin converter
throws error in function if input is below absolute 0
*/
#include "section5.h"

// converts Celsius to Kelvin
double ctok(double c_to_k)
{
	//throw error if value given in Celsius is below -273.15
	if (c_to_k < -273.15)
	{
		error("Can not be below absolute zero!\n");
	}
	c_to_k += 273.15;
	return c_to_k;
}

int main()
try
{
	std::cout << "Enter a temperature in Celsius to covert to Kelvin:\n";
	double celsius = 0;
	std::cin >> celsius;
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
