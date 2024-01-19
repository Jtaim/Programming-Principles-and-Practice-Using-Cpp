/*
    Written by Jtaim
    Date 11 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 12
    Improve print_until_s() from 8.5.2. 
    Test it. 
    What makes a good set of test cases? Give reasons. 
    Then, write a print_until_ss() that prints until it sees a second occurrence of its quit argument.
*/

#include"../includes/ppp.hpp"

void print_until_s( const std::vector<std::string>& v, const std::string_view quit )
{
    for( const auto& s : v )
    {
        if( s == quit )
        {
            return;
        }
        std::cout << s << '\n';
    }
}

void print_until_ss( const std::vector<std::string>& v, const std::string_view quit)
{
    if( !v.empty() )
    {
        unsigned int i{};
        for( const auto& s : v )
        {
            if( s == quit )
            {
                ++i;
                if( i == 2 )
                {
                    return;
                }
            }
            std::cout << s << '\n';
        }
        if( i < 2 )
        {
            std::cout << "No " << quit << " found.";
        }
    }
    else
    {
        std::cout << "no strings found";
    }
    std::cout << "\n";
}

int main()
{
    std::vector<std::string> v1{ "zero","one", "two", "eight", "two", "three", "four" };
    std::vector<std::string> v2{};

    const std::string quit{ "two" };

    std::cout << "numbers:\n";
    print_until_s( v1, quit );

    std::cout << "numbers:\n";
    print_until_ss( v1, quit );

    std::cout << "numbers:\n";
    print_until_ss( v2, quit );

    ppp::keep_window_open();
    return 0;
}
