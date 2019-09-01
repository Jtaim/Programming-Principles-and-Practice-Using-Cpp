//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 2.
converts from miles to kilometers (1.609 kilometers to the mile)
*/

#include "section3.h"

int main()
{
	using namespace std;

	cout << "Enter the number of miles you want to convert to kilometers: ";
	double miles{};
	if(cin >> miles){
		cout << miles << " miles converted to kilometers is " << miles * 1.609 << endl;
	} else{
		simple_error("Invalid entry");
	}

	keep_window_open();
	return 0;
}
