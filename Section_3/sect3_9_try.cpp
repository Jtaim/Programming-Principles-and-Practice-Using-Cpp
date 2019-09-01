//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3.9 try this exercise
*/

#include "section3.h"

//exit EOF or ctrl-z
int main()
{
	using namespace std;

	double d{};
	cout << "Shows how C++ implicitly converts types. EOF to exit\n";
	while(cin >> d){
		int i = d;	// conversion from 'double' to 'int', possible loss of data
		//int j {d};  // the {} enforce error narrowing error
		char c = i; // conversion from 'int' to 'char', possible loss of data
		int i2 = c; // OK, get the integer value of the character
		cout << "the entered double value: " << d << endl
			<< "double converted to int: " << i << endl
			<< "int converted to char: " << c << endl
			<< "char converted to int: " << i2 << endl;
	}

	keep_window_open();
	return 0;
}
