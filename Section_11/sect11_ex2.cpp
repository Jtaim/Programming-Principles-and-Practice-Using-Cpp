/*
    Written by Jtaim
    Date 19 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 2
    Write a program that given a file name and a word outputs each line that contains that word together with the line number.
    Hint: getline().
*/

#include "ppp.hpp"

int main()
try
{
    constexpr std::string_view word_match{ "return" };
    std::ifstream ifs{ "sect11_ex2.cpp" };
    std::string line;
    for( size_t line_number{ 1 }; std::getline( ifs, line ); ++line_number )
    {
        if( std::string::npos != line.find( word_match ) )
        {
            std::cout << line_number << line << "\n";
        }
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
