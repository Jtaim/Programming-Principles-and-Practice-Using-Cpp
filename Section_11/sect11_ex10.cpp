/*
    Written by Jtaim
    Date 24 Nov 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Section 11 Exercise 10
    Write a function vector<string> split(const string& s) that returns a vector of whitespace-separated substrings
    from the argument s.
*/

#include"ppp.hpp"
#include <print>

std::vector<std::string> split( const std::string &s );

int main()
try
{
    constexpr std::string_view str{ "Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition." };
    auto white_space{ split( str.data() ) };

    for( auto &s : white_space )
    {
        std::println( "{}", s );
    }

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

std::vector<std::string> split( const std::string &s )
{
    std::vector<std::string> strings;
    std::istringstream is{ s };
    for( std::string str; is >> str; )
    {
        strings.push_back( str );
    }
    return strings;
}
