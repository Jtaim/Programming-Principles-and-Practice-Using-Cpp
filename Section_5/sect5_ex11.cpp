//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 11
A program that writes out the Fibonacci series up to largest to fit in an int type
*/

#include "section5.h"

unsigned sum(unsigned, unsigned);

int main()
try
{
    std::vector<unsigned> fibonacci{ 0,1 };
    for (unsigned i = 0; ; ++i) {
        std::cout << fibonacci[i] << '\n';
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
unsigned int sum(unsigned var1, unsigned var2)
{
    if ((var2 > 0) && (var1 > UINT_MAX - var2)) {
        error("unsigned int max overflow error");
    }
    return var1 + var2;
}
