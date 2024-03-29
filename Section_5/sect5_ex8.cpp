//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 8
A program that reads and stores a series of integers.
Ask user to enter number(N) of integers want to sum.
Create a vector of the first N integers.
From that vector calculate the sum of those N integers.
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.hpp"

int main()
try
{
    constexpr char termination{ '|' };
    using vType = std::vector<int>;

    std::cout << "Enter how many numbers that you would like to sum:\n";

    int number_to_sum{};
    if( !( std::cin >> number_to_sum ) )
    {
        error( "number expected!" );
    }

    vType numbers;
    std::cout << "Enter some numbers (press '" << termination << "' to stop)\n";
    //for loop to get integers to place in a vector, validate and exit on an '|' entry
    for( char c{}; c != termination; /* */ )
    {
        vType::value_type number{};
        // loads entered numbers into a vector container 
        if( std::cin >> number )
        {
            numbers.push_back( number );
        }
        else
        {
            std::cin.clear();
            std::cin >> c;
            if( c != termination )
            {
                error( "Invalid number or termination!" );
            }
        }
    }

    if( numbers.size() < number_to_sum )
    {
        error( "not enough numbers entered to sum!" );
    }

    auto stop{ numbers.begin() + number_to_sum };
    vType::value_type sum{};
    std::cout << "The sum of the first " << number_to_sum << " numbers ";
    for( auto i{ numbers.begin() }; i != stop; ++i )
    {
        sum += *i;
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
