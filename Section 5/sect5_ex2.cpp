//written by Jtaim
//date 31 Oct 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
sect 5 exercise 2
find errors and document
*/
#include "section5.h" //custom header

//double ctok(double c) // converts Celsius to Kelvin
//just style but set variable c as constant
double ctok(const double c) // converts Celsius to Kelvin
{
	//int k = c + 273.15;
	//use double prevent narrow errors
	//use descriptive variable names
	double c_to_k = c + 273.15;
	//return int;
	//compile error: type name is not allowed
	return c_to_k;
}

int main()
{
	double c = 0; //input variable
	//cin >> d;
	//compile error: identifier "d" is undefined
	cin >> c;
	//double k = ctok("c");
	//compile error: argument error
	double k = ctok(c);
	//Cout << k << '\n';
	//compile error: identifier "Cout" is undefined
	cout << k << '\n';
	
	keep_window_open();
	return 0;
}