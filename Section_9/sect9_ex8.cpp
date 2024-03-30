/*
    Written by Jtaim
    Date 20 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 8
    Design and implement a Patron class under library namespace
*/

#include"../includes/ppp.hpp"

#include "Patron.hpp"

int main()
try
{
    library::Patron patron{ "John Doe", 123456 };
    if( !patron.is_outstanding_fee() )
    {
        std::cout << std::format( "{} outstanding fees ${}\n", patron.get_name(), patron.get_fees() );
    }

    patron.set_fees( 0.01 );
    std::cout << std::format( "{} outstanding fees ${}\n", patron.get_name(), patron.get_fees() );


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