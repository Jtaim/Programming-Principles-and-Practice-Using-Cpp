/*
    Written by Jtaim
    Date 12 Jan 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Drill 8
    Try reading as octal, hexadecimal, etc.:
    cin >> a >> oct >> b >> hex >> c >> d;
    cout << a << '\t'<< b << '\t'<< c << '\t'<< d << '\n';
    Run this code with the input 1234 1234 1234 1234 Explain the results.
*/

#include "ppp.hpp"

int main()
try
{
    int a{}, b{}, c{}, d{};
    std::cin >> a >> std::oct >> b >> std::hex >> c >> d;
    std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

    // the output keeps previous set base until it is changed or program restarted.
    // you have to explicitly change the base.
    // the value is stored as the base value, so be careful

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
