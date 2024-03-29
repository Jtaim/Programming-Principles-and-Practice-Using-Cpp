/*
    Written by Jtaim
    Date 22 Dec 2018
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 6
    Write 2 functions that reverse the element order in a vector<string>.
    One function should produce a new vector with the elements reversed, not affecting the original vector.
    The other should reverse the elements with out using a new vector.
*/

#include "..\includes\ppp.hpp"

#include<iostream>
#include<string>
#include<vector>

using strvec = std::vector<std::string>;

void reverse( const strvec& v, strvec& rv )
{
    rv.clear();
    if( !v.empty() )
    {
        for( auto iv{ v.crbegin() }; iv != v.crend(); ++iv )
        {
            rv.push_back( *iv );
        }
    }
}

void reverse( strvec& v )
{
    if( !v.empty() )
    {
        for( auto itr = v.begin(), ritr = v.end() - 1; itr < ritr; ++itr, --ritr )
        {
            std::string temp = std::move( *itr );
            *itr = *ritr;
            *ritr = std::move( temp );
        }
    }
}

int main()
{
    strvec a{ "zero","one","two","three","four","five" };
    strvec b;

    reverse( a, b );
    std::cout << "vector a: ";
    for( auto n : a )
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    std::cout << "vector b: ";
    for( auto n : b )
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    // ----------------------------------

    reverse( a );
    std::cout << "\n\nvector a: ";
    for( auto n : a )
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    reverse( b );
    std::cout << "vector b: ";
    for( auto n : b )
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    ppp::keep_window_open();
    return 0;
}
