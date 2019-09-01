// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3 exercise 4.
A program that prompts the user to enter two integer values.
Store these values in int variables named val1 and val2.
*/

#include "section3.h"

int main()
{
	using namespace std;

	cout << "Enter two integer values:\n";
	int val1{};
	int val2{};

	if(!(cin >> val1 >> val2)){
		simple_error("Invalid entry!");
	}

	if(val1 < val2){
		cout << val1 << " is smaller than " << val2 << endl;
	} else if(val1 > val2){
		cout << val2 << " is smaller than " << val1 << endl;
	} else if(val1 == val2){
		cout << val1 << " is equal to " << val2 << endl;
	} else{
		simple_error("Not sure how I got here?");
	}

	cout << "The sum of " << val1 << " and " << val2 << " is " << val1 + val2 << endl;
	cout << "The difference of " << val1 << " and " << val2 << " is " << val1 - val2 << endl;
	cout << "The product of " << val1 << " and " << val2 << " is " << val1 * val2 << endl;
	if(val2 == 0){
		simple_error("I don't divide by zero");
	} else{
		cout << "The ratio of " << val1 << " and " << val2 << " is " << static_cast<double>(val1) / static_cast<double>(val2) << endl;
	}

	keep_window_open();
	return 0;
}
