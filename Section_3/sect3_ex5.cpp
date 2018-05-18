// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3 exercise 5
repeat exercise 4 using double values
Write your program to determine the smaller, larger, sum, difference, 
product, and ratio of these values and report them to the user.
*/

#include "section3.h" //custom header

int main()
{
	using namespace std;

	cout << "Enter two double values:\n";
	double val1{ 0.0 };
	double val2{ 0.0 };

	if (!(cin >> val1 >> val2)) { simple_error("Invalide entry!"); }
	if (val1 < val2) {
		cout << val1 << " is smaller than " << val2 << endl;
	}
	else if (val1 > val2) {
		cout << val2 << " is smaller than " << val1 << endl;
	}
	else if (val1 == val2) {
		cout << val1 << " is equal to " << val2 << endl;
	}
	else { simple_error("not sure how got here?"); }

	cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 << endl;
	cout << "The difference of " << val1 << " and " << val2 << " is " << val1 - val2 << endl;
	cout << "The product of " << val1 << " and " << val2 << " is " << val1 * val2 << endl;
	if (val2 == 0) { simple_error("I don't divide by zero\n"); }
	else {
		cout << "The ration of " << val1 << " and " << val2 << " is " << val1 / val2 << endl;
	}
	keep_window_open();
	return 0;
}
