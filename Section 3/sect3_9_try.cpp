//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3.9 try this exercise
*/

#include "section3.h" //custom header

//exit EOF or ctrl-z
int main()
{
	using namespace std;

	double d{ 0.0 };
	cout << "show some basic of how C++ converts types. EOF to exit\n";
	while (cin >> d)
	{
		int i{ static_cast<int>(d) };	// try to squeeze a double into an int
		//int j {d};						// the {} enforce error narrowing error
		char c{ static_cast<char>(i) }; // try to squeeze an int into a char
		int i2 = c;             		// get the integer value of the character
		cout << "the entered double value " << d << "\n"
			 << "double converted to int " << i << "\n"
			 << "int converted to char (" << c << ")\n"
			 << "char converted to int " << i2 << "\n";
	}
	return 0;
}
