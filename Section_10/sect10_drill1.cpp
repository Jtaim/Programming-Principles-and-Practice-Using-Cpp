/*
    Written by Jtaim
    Feb 26 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 10 Drill 1
    Start a program to work with points, discussed in section 10.4.
    Begin by defining the data type Point that has two coordinate members x and y.
*/

#include "../includes/ppp.hpp"
#include "Point.hpp"

int main()
try
{
    Point<int> a;
    Point b{ 2, 3 };

    if( a != b ) {}
    std::cout << "Point a: " << a << "\n";
    std::cout << "Point b: " << b << "\n";

    if( !( std::cin >> a ) && !std::cin.eof() )
    {
        std::cout << "bad input\n";
    }
    else
    {
        std::cout << "Point a: " << a << "\n";
    }

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}
