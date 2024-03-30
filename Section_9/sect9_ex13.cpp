/*
    Written by Jtaim
    Date 31 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 13
    this is the test program Rational class.
*/

#include"../includes/ppp.hpp"

#include "Rational.hpp"

int main()
try
{
    Rational r1{ 4,8 };
    std::cout << "r1 = " << r1.get_numerator() << '/' << r1.get_denominator() << '\n';

    Rational r2{ 3,12 };
    std::cout << "r2 = " << r2.get_numerator() << '/' << r2.get_denominator() << '\n';

    auto r3 = r1 + r2;
    std::cout << "r3 = " << r3.get_numerator() << '/' << r3.get_denominator() << '\n';

    auto r4 = r3 - Rational( 2, 7 );
    std::cout << "r4 = " << r4.get_numerator() << '/' << r4.get_denominator() << '\n';

    auto r5 = r1 * Rational( 1, 2 );
    std::cout << "r5 = " << r5.get_numerator() << '/' << r5.get_denominator() << '\n';

    auto r6 = r1 / Rational( 3, 16 );
    std::cout << "r6 = " << r6.get_numerator() << '/' << r6.get_denominator() << '\n';

    double r7 = r6;
    std::cout << "r7 = " << r7 << '\n';

    ppp::keep_window_open();
    return 0;
}
catch( std::exception& e )
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
