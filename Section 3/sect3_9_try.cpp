//written by Jtaim
//date 18 Sept 2015
//updated 1 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3.9 try this exercise
*/

#include <iostream>
#include <string>
#include "section3.h" //custom header

//C++ programs start by executing the function main
//exit EOF ctrl-z
int main()
{
	using namespace std;
	double d = 0;
	std::cout << "show some basic of how C++ converts types. EOF to exit\n";
	while (cin >> d)
	{
		int i = d;						// try to squeeze a double into an int
		//int i {d};						// the {} enforce error narrowing error
		char c = i;            			// try to squeeze an int into a char
		int i2 = c;             		// get the integer value of the character
		cout << "the entered double value " << d << "\n"
			<< "double converted to int " << i << "\n"
			<< "int converted to char (" << c << ")\n"
			<< "char converted to int " << i2 << "\n";
	}
	return 0;
}
