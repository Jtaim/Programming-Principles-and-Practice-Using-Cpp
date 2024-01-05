//written by Jtaim
//date 6 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
section 5 exercise 7.
build upon section 4 exercise 18.
Write a program to solve quadratic equations(ax^2+bx+c=0).
x = (-b +/- sqrt(b^2-4ac))/2a
Check that b^2-4ac is not less than 0.
Write a function that print out the roots of a quadratic equation, given a,b,c.
If no real roots print out a message.
example of 1 real square root is x^2 + 6x + 9
example of 2 real square roots is x^2 - 3x + 2
example of 2 complex roots is -3x^2 + 2x - 1
*/

#include "section5.h"
#include <complex>

static void quadratic( const double a, const double b, const double c )
{
    if( a == 0.0 )
    {
        error( "a = 0; so can not derive any roots\n" );
    }
    auto sq{ b * b - 4.0 * a * c };
    //When b^2 - 4ac == 0 there is one real root.
    if( sq == 0.0 )
    {
        std::cout << "x = " << -1.0 * b / ( 2 * a ) << std::endl;
    }
    //When b^2 - 4ac > 0 there are two real roots.
    else if( sq > 0.0 )
    {
        std::cout << "x = " << ( -1.0 * b + sqrt( sq ) ) / ( 2.0 * a ) << std::endl;
        std::cout << "x = " << ( -1.0 * b - sqrt( sq ) ) / ( 2.0 * a ) << std::endl;
    }
    //When b^2 - 4ac < 0 there are two complex roots.
    else
    {
        std::cout << "x = " << ( -1.0 * b ) / ( 2.0 * a ) << " + " << sqrt( fabs( sq ) ) / ( 2.0 * a ) << "i" << std::endl;
        std::cout << "x = " << ( -1.0 * b ) / ( 2.0 * a ) << " - " << sqrt( fabs( sq ) ) / ( 2.0 * a ) << "i" << std::endl;
    }
}

int main()
try
{
    std::cout << "Enter the a, b and c variables to solve the quadratic equation:\n";
    double a{};
    double b{ 1.0 };
    double c{};
    if( !( std::cin >> a >> b >> c ) )
    {
        error( "a non-numeric number entered." );
    }

    quadratic( a, b, c );

    keep_window_open();
    return 0;
}
catch( std::exception& e )
{
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}
