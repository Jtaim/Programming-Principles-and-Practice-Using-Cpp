//written by Jtaim
//date 6 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 11
A program that writes out the Fibonacci series up to largest to fit in an int type
*/

#include "section5.h"

int sum(int, int);

int main()
try
{
	vector<int> fibonacci{ 0, 1 };
	for (int i = 0; ; ++i) {
		//cout << fibonacci[i+1] << '\n';
		fibonacci.push_back(sum(fibonacci[i], fibonacci[i+1]));
	}
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
/*	Sums 2 integer values.
Inputs:		int, int
Outputs:	sum
Errors:		if the sums overflow int type
*/
int sum(int var1, int var2)
{
	if ((var2 > 0) && (var1 > INT_MAX - var2)) {
		cout << var2 << " is the max Fibonacci series number to fit in an int type.\n";
		error("int max overflow error");
	}
	//if ((var2 < 0) && (var1 < INT_MAX - var2)) {
	//	error("int min overflow error");
	//}
	return var1 + var2;
}