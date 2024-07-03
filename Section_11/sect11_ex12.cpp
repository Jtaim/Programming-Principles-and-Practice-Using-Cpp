/*
    Written by Jtaim
    Date 30 June 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 12
    Reverse the order of characters in a text file.
    For example, asdfghjkl becomes lkjhgfdsa.
    Warning: There is no really good, portable, and efficient way of reading a file backward.
*/

#include "ppp.hpp"
#include <print>

constexpr std::string_view ascii_file{ "sect11_ex12.txt" };
constexpr std::string_view str{ "asdfghjkl" };

int main()
try
{
    // create file with some text data
    std::ofstream ofs{ ascii_file.data() };
    if( !ofs )
    {
        ppp::error( std::format( "could not open {}", ascii_file ) );
    }
    ofs << str;

    ofs.close();
    std::ifstream ifs{ ascii_file.data() };
    if( !ifs )
    {
        ppp::error( std::format( "could not open {}", ascii_file ) );
    }

    // get data from the file
    std::vector<char> vc;
    for( char c{}; ifs.get( c ); )
    {
        vc.push_back( c );
        std::print( "{}", c );
    }
    std::cout << std::endl;

    // put reversed data back into the file
    ifs.close();
    ofs.open( ascii_file.data() );
    for( auto itr{ vc.rbegin() }; itr != vc.rend(); ++itr )
    {
        ofs.put( *itr );
    }

    // read the reversed contents
    ofs.close();
    ifs.open( ascii_file.data() );
    for( char c{}; ifs.get( c ); )
    {
        std::print( "{}", c );
    }
    std::cout << std::endl;

    ppp::keep_window_open();
    return 0;
}
catch( std::exception &e )
{
    std::println( "exception: {}", e.what() );
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::println( "exception" );
    ppp::keep_window_open();
    return 2;
}
