/*
    Written by Jtaim
    Date 20 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 9 Exercise 5
    Design and implement a Book class under library namespace
    -
*/

#include"../includes/ppp.hpp"

#include "Book.hpp"

std::string book_status( const library::Book& b )
{
    return std::move( std::format(
        "ISBN: {}\n"
        "TITLE: {}\n"
        "AUTHOR: {}\n"
        "COPYRIGHT: {}\n"
        "checked out: {}\n\n",
        b.get_isbn(), b.get_title(), b.get_author(), b.get_copyright(), b.is_checked_out() ) );
}

int main()
try
{
    library::Book book( "0-321-99278-4", "Programming Principles and Practices Using C++ Second Edition", "Bjarne Stroustrup", 2014 );
    std::cout << book_status( book );

    book.check_inout( true );
    std::cout << book_status( book );

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
