//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 9
A program that reads and stores a series of integers.
Ask user to enter number(N) of integers want to sum.
Create a vector of the first N integers.
From that vector calculate the sum of those N integers.
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector

Added overflow error when summing
*/

#include "section5.h"

using vType = std::vector<int>;

/*	addition function.
  Inputs:		two numbers
  outputs:	    valid resulting number
  Errors:		element overflow
*/
static vType::value_type add( vType::value_type n1, vType::value_type n2 )
{
    if( ( ( n2 > 0 ) && ( n1 > ( std::numeric_limits< vType::value_type>::max() - n2 ) ) ) ||
        ( ( n2 < 0 ) && ( n1 < ( std::numeric_limits< vType::value_type>::min() - n2 ) ) ) )
    {
        error( "overflowed integer type!" );
    }
    auto n = n1 + n2;
    return n;
}

int main()
try
{
    constexpr char termination{ '|' };

    std::cout << "Enter how many numbers that you would like to sum:\n";

    int number_to_sum{};
    if( !( std::cin >> number_to_sum ) || number_to_sum < 1 )
    {
        error( "positive integer expected!" );
    }

    // vector to hold the entered numbers
    vType numbers;
    std::cout << "Enter some numbers (press '" << termination << "' to stop)\n";
    //for loop to get integers to place in a vector, validate and exit on an '|' entry
    for( char c{}; c != termination; /* */ )
    {
        vType::value_type number{};
        // loads entered numbers into a vector container 
        std::cin >> number;
        if( std::cin.good() )
        {
            numbers.push_back( number );
        }
        else
        {
            // check for proper termination
            // Visual Studio detects an overflow with a failed input flag and leaves the space or new line character in the buffer. 
            std::cin.clear();
            std::cin.get( c );
            if( c == ' ' || c == '\n' )
            {
                error( "overflow input integer!" );
            }
            if( c != termination )
            {
                error( "Not the correct termination!" );
            }
        }
    }

    // do we have some numbers ?
    if( numbers.size() < number_to_sum )
    {
        error( "not enough numbers entered to sum!" );
    }

    auto stop{ numbers.begin() + number_to_sum };
    vType::value_type sum{};
    std::cout << "The sum of the first " << number_to_sum << " numbers ";
    for( auto i{ numbers.begin() }; i != stop; ++i )
    {
        sum = add( sum, *i );
        std::cout << *i << ( i == ( stop - 1 ) ? " = " : " + " );
    }
    std::cout << sum << std::endl;

    keep_window_open();
    return 0;
}
catch( std::exception& e )
{
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}
