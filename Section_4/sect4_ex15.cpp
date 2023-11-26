//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
 Section 4 exercise 15.
 A program that takes an input value n and then finds the first n primes
*/

#include "section4.h"

int main()
{
    // container to store the prime numbers
    std::vector<std::size_t> primes{};

    std::size_t wantedPrimes{};
    std::cout << "enter number of primes you want to find." << std::endl;
    if( !( std::cin >> wantedPrimes ) )
    {
        simple_error( "entered invalid integer value\n" );
    }

    // loop to found n primes and start with 2.
    for( std::size_t i{ 2 }; primes.size() < wantedPrimes; ++i )
    {
        auto check = std::find_if( primes.cbegin(), primes.cend(), [i]( auto p ) { return i % p == 0; } );
        if( check == primes.cend() )
        {
            primes.push_back( i );
        }
    }

    // print out the prime numbers
    std::cout << std::format("The number of primes found is {}.\n", primes.size());
    for( int j{ 1 }; auto x : primes )
    {
        //10 per row
        std::cout << x << ( j % 10 != 0 ? '\t' : '\n' );
        ++j;
    }
    std::cout << std::endl;

    keep_window_open();
    return 0;
}
