//written by Jtaim
//date 6 Nov 2015
//updated 20 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 11
A program that writes out the Fibonacci series up to largest to fit in an int type
*/

#include "section5.h"

unsigned int sum(unsigned int, unsigned int);

int main()
try
{
	std::vector<unsigned int> fibonacci{ 0, 1 };
	for (unsigned int i = 0; ; ++i)
	{
		std::cout << fibonacci[i+1] << '\n';
		fibonacci.push_back(sum(fibonacci[i], fibonacci[i + 1]));
	}
	keep_window_open();	// yes I know will never get to this point
	return 0;
}
catch (std::exception& e)
{
	std::cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...)
{
	std::cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

/*	Sums 2 unsigned integer values.
Inputs:		unsigned int, unsigned int
Outputs:	sum
Errors:		if the sums overflow unsigned int type
*/
unsigned int sum(unsigned int var1, unsigned int var2)
{
	if ((var2 > 0) && (var1 > UINT_MAX - var2))
	{
		std::cout << var2 << " is the max Fibonacci series number to fit in an unsigned int type.\n";
		error("unsigned int max overflow error");
	}
	//if ((var2 < 0) && (var1 < UINT_MAX - var2))
	//{
	//	error("unsigned int min overflow error");
	//}
	return var1 + var2;
}
