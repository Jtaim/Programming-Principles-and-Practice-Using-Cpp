//written by Jtaim
//date 1 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 3
Celsius to Kelvin converter
throws error in main if input is below absolute 0
*/
#include "section5.h" //custom header

double ctok(const double c) // converts Celsius to Kelvin
{
	double c_to_k = c + 273.15;
	return c_to_k;
}

int main()
try
{
	cout << "Enter a temperature in Celsius to covert to Kelvin:\n";
	double c = 0; //input variable
	cin >> c;
	if (c < -273.15) {
		error("Can not be below absolute zero!\n");
	}
	double k = ctok(c);
	cout << k << '\n';
	
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