/*
    Written by Jtaim
    Date 12 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 13
    Can we declare a non-reference function const (e.g., void f(const int);)?
    - yes.
    What might that mean?
    - read only argument.  functional will not modify the argument is a compiler error if you try.
    Why don't people do that often?
    - not sure but should always assign as const if function is not modifying an argument.
*/

#include"../includes/ppp.h"

void f(const int n)
{
    //n = 25;

    std::cout << n << std::endl;
}

int main()
{
    int arg{15};
    f(arg);

    arg = 69;
    f(arg);

    ppp::keep_window_open();
    return 0;
}