//written by Jtaim
//date 1 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 6
Celsius to Fahrenheit converter
Fahrenheit to Celsius converter
*/
#include "section5.h" //custom header

double ctof(const double &c) // converts Celsius to Fahrenheit f=9/5*c+32
{
	if (c < -273.15) {  //throw error if value given in Celsius is below -273.15
		error("ctof can not convert below absolute zero!\n");
	}double c_to_f = 9.0/5 * c + 32;
	return c_to_f;
}
double ftoc(const double &f) // converts Kelvin to Celsius
{
	double f_to_c = 5.0/9 * (f - 32);
	if (f_to_c < -273.15) {  //throw error if value given in Celsius is below -273.15
		error("ftoc can not convert below absolute zero!\n");
	}
	return f_to_c;
}

int main()
try
{
	cout << "Enter a temperature and unit of temperature (c = Celsius, f = Fahrenheit)\n";

	double temp_to_convert = 0; //input temperature variable
	cin >> temp_to_convert;
	if (cin.fail()) {
		cin.clear();  //clear cin error flags
		cin.ignore(INT_MAX, '\n'); //clear cin buffer
		error("entered non-numeric temperature!\n");
	}

	char entered_temp_unit = '?';
	cin >> entered_temp_unit;
	entered_temp_unit = tolower(entered_temp_unit);

	double converted_temp = 0;
	char converted_temp_unit = '?';
	switch (entered_temp_unit) {
	case 'f' : 
		converted_temp = ftoc(temp_to_convert);
		converted_temp_unit = 'c';
		break;
	case 'c' : 
		converted_temp = ctof(temp_to_convert);
		converted_temp_unit = 'f';
		break;
	default : 
		error("entered wrong temperature unit of measure!\n");
	}
	cout << "Converted temperature is " << converted_temp << " " << converted_temp_unit << '\n';
	
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