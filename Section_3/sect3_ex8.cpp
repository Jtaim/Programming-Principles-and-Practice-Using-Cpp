// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3 exercise 8.
A program to test an integer value to determine if it is odd or even.
As always, make sure your output is clear and complete.
In other words, don’t just output yes or no. Your output should stand alone,
like The value 4 is an even number. Hint: See the remainder (modulo) operator in section 3.4.
*/

#include "section3.h"

int main()
{
	using namespace std;

	cout << "Enter an integer: ";
	int val{};
	if(!(cin >> val)){
		simple_error("Invalid integer value\n");
	}
	cout << "The value " << val << " is an " << ((val % 2) ? "odd" : "even") << " number.\n";

	keep_window_open();
	return 0;
}
