/*
    Written by Jtaim
    Date 22 Dec 2018
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 8 Exercise 4
    using previous exercise to approximate the max limit of int type.
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

int fibonacci( const int x, const int y, std::vector<int>& v, const int n )
{
    int max{};
    v.push_back( x );
    v.push_back( y );
    for( int i{}; i < ( n - 2 ); ++i )
    {
        auto num{ v.at( i ) + v.at( i + 1 ) };
        if( num < v.at( i + 1 ) )
        {
            max = v.at( i + 1 );
            break;
        }
        v.push_back( num );
    }
    return max;
}

int main()
{
    int max_found{};
    std::vector<int> vi;
    std::vector<int> winner;
    for( int x{ 1 }; x < 1000; ++x )
    {
        int y{ x * 2 };
        auto returned_value{ fibonacci( x, y, vi, 100 ) };
        if( returned_value > max_found )
        {
            winner.clear();
            winner = vi;
            max_found = returned_value;
        }
        vi.clear();
    }

    auto str = std::format("Print a Fibonacci sequence of length equal to {} and starting with {} and {}.",
                            winner.size(), winner.at( 0 ), winner.at( 1 ));
    print( str, winner );


    std::cout << "\nThe approximate maximum limit on an \"int\" type is " << max_found << std::endl;

    ppp::keep_window_open();
    return 0;
}

/*
if got this when ran for loops at 1000000 iterations.
WARNING MAY TAKE A MINUTE OR TWO

the approximate maximum limit on an "int" type is 2147482849
Print a Fibonacci sequence of length equal to 18 and starting with 513629 and 1027258.
513629
1027258
1540887
2568145
4109032
6677177
10786209
17463386
28249595
45712981
73962576
119675557
193638133
313313690
506951823
820265513
1327217336
2147482849
*/

