//written by Jtaim
//date 1 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 4
Celsius to Kelvin converter
throws error in function if input is below absolute 0
*/
#include "section5.h" //custom header

double ctok(const double &c) // converts Celsius to Kelvin
{
	if (c < -273.15) {  //throw error if value given in Celsius is below -273.15
		error("Can not be below absolute zero!\n");
	}
	double c_to_k = c + 273.15;
	return c_to_k;
}

int main()
try
{
	cout << "Enter a temperature in Celsius to covert to Kelvin:\n";
	double celsius = 0; //input temperature variable
	cin >> celsius;
	double kelvin = ctok(celsius); 
	cout << kelvin << '\n';
	
	keep_window_open();
	return 0;
}
catch (exception& e)
{
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...)
{
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}