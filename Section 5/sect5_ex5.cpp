//written by Jtaim
//date 1 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 5
Celsius to Kelvin converter
Added Kelvin to Celsius converter
*/
#include "section5.h" //custom header

double ctok(const double &c) // converts Celsius to Kelvin
{
	if (c < -273.15) {  //throw error if value given in Celsius is below -273.15
		error("ctok can not convert below absolute zero!\n");
	}
	double c_to_k = c + 273.15;
	return c_to_k;
}
double ktoc(const double &k) // converts Kelvin to Celsius
{
	if (k < 0) {  //there are no negative kelvin values
		error("ktoc can not convert below absolute zero!\n");
	}
	double k_to_c = k - 273.15;
	return k_to_c;
}

int main()
try
{
	cout << "Enter a temperature and unit of temperature (c = Celsius, k = Kelvin)\n";

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
	case 'c' : 
		converted_temp = ctok(temp_to_convert);
		converted_temp_unit = 'k';
		break;
	case 'k' : 
		converted_temp = ktoc(temp_to_convert);
		converted_temp_unit = 'c';
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