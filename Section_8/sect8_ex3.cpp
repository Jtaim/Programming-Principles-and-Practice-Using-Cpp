/*
    Written by Jtaim
    Date 21 Dec 2018
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 3
    Create a vector of Fibonacci numbers and print them using the function from exercise 2.
    To create the vector, write a function, fibonacci ( x , y , v , n ),
    where x and y are ints,
    v is an empty vector < int >,
    and n is the number of elements to put into v;
    v[0] will be x and v[1] will be y.
    A fibonacci number is one that is part of a sequence where each element is the sum of the two previous ones.
    For example, starting with 1 and 2, we get 1, 2, 3, 5, 8, 13, 21, . . . .
    Your Fibonacci( ) function should make such a sequence starting with its x and y arguments.

*/

#include "..\includes\ppp.hpp"

#include<iostream>
#include<string>
#include<vector>

void print( const std::string& label, const std::vector<int>& v )
{
    std::cout << label << '\n';
    for( auto i : v )
    {
        std::cout << i << '\n';
    }
}

void fibonacci( const int x, const int y, std::vector<int>& v, const int n )
{
    v.push_back( x );
    v.push_back( y );
    for( int i{}; i < ( n - 2 ); ++i )
    {
        v.push_back( v.at( i ) + v.at( i + 1 ) );
    }
}

int main()
{
    int x{ 1 };
    int y{ 2 };
    int how_many{ 10 };

    auto str = std::format("Print a Fibonacci sequence of length equal to {} and starting with {} and {}.", how_many, x, y);

    std::vector<int> vi;

    fibonacci( x, y, vi, how_many );
    print( str, vi );

    ppp::keep_window_open();
    return 0;
}
