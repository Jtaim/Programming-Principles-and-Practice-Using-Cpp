//written by Jtaim
//date 5 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 5
Celsius to Kelvin converter
Added Kelvin to Celsius converter
*/
#include "section5.h"

// converts Celsius to Kelvin
double ctok(double c)
{
	if (c < -273.15) {
		//throw error if value given in Celsius is below -273.15
		error("ctok can not convert below absolute zero!\n");
	}
	c += 273.15;
	return c;
}
// converts Kelvin to Celsius
double ktoc(double k)
{
	if (k < 0) {
		//there are no negative kelvin values
		error("ktoc can not convert below absolute zero!\n");
	}
	k -= 273.15;
	return k;
}

int main()
try
{
	bool badConversion;
	do {
		badConversion = false;
		std::cout << "Enter a temperature and unit of temperature (c = Celsius, k = Kelvin)\n";
		double temp_to_convert{ 0 };
		while (!(std::cin >> temp_to_convert)) {
			std::cin.clear();  //clear cin error flags
			std::cin.ignore(UINT8_MAX, '\n'); //clear cin buffer
			std::cout << "entered non-numeric temperature. Re-eneter temperature\n";
		}
		char entered_temp_unit{ '?' };
		std::cin >> entered_temp_unit;
		double converted_temp{ 0 };
		char converted_temp_unit{ '?' };
		switch (entered_temp_unit) {
		case 'c':
		case 'C':
			converted_temp = ctok(temp_to_convert);
			converted_temp_unit = 'k';
			break;
		case 'k':
		case 'K':
			converted_temp = ktoc(temp_to_convert);
			converted_temp_unit = 'c';
			break;
		default:
			badConversion = true;
			std::cout << "entered wrong temperature unit of measure.  Re-renter conversion\n";
		}
		if (badConversion == false) {
			std::cout << "Converted temperature is " << converted_temp << converted_temp_unit << '\n';
		}
	} while (badConversion);
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
