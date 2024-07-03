/*
    Written by Jtaim
    Date 30 June 2024
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 13
    Reverse the order of words (defined as whitespace-separated strings) in a file.
    For example, Norwegian Blue parrot becomes parrot Blue Norwegian.
    You are allowed to assume that all the strings from the file will fit into memory at once.
*/

#include "ppp.hpp"
#include <print>

constexpr std::string_view string_file{ "sect11_ex13.txt" };
constexpr std::string_view str{ "Norwegian Blue parrot" };

int main()
try
{
    // create file with some text data
    std::ofstream ofs{ string_file.data() };
    if( !ofs )
    {
        ppp::error( std::format( "could not open {}", string_file ) );
    }
    ofs << str;

    ofs.close();
    std::ifstream ifs{ string_file.data() };
    if( !ifs )
    {
        ppp::error( std::format( "could not open {}", string_file ) );
    }

    // get data from the file
    std::vector<std::string> vstr;
    for( std::string s; ifs >> s; )
    {
        vstr.push_back( s );
        std::print( "{} ", s );
    }
    std::cout << std::endl;

    // put reversed data back into the file
    ifs.close();
    ofs.open( string_file.data() );
    for( auto itr{ vstr.rbegin() }; itr != vstr.rend(); ++itr )
    {
        ofs << ( *itr + ' ' );
    }

    // read the reversed contents
    ofs.close();
    ifs.open( string_file.data() );
    for( std::string s; ifs >> s; )
    {
        std::print( "{} ", s );
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
