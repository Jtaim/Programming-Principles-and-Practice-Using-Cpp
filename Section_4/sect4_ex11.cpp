//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 11.
 Create a program to find all the prime numbers between 1 and 100.
 One way to do this is to write a function that will check if a number is prime
 (i.e., see if the number can be divided by a prime number smaller than itself)
 using a vector of primes in order (so that if the vector is called primes, primes[0]==2, primes[1]==3, primes[2]==5, etc.).
 Then write a loop that goes from 1 to 100, checks each number to see if it is a prime, and stores each prime found in a vector.
 Write another loop that lists the primes you found.
 You might check your result by comparing your vector of prime numbers with primes. Consider 2 the first prime.
*/

#include "section4.h"

int main()
{
    int constexpr max{ 100 };

    // container to store the prime numbers
    std::vector<int> primes{};

    // start with 2
    for( int i{ 2 }; i <= max; ++i )
    {
        auto check = std::find_if( primes.cbegin(), primes.cend(), [i]( auto p ) { return i % p == 0; } );
        if( check == primes.cend() )
        {
            primes.push_back( i );
        }
    }

    // print out the prime numbers
    for( int j{ 1 }; auto x : primes )
    {
        //10 per row
        std::cout << x << ( j % 10 != 0 ? '\t' : '\n' );
        ++j;
    }

    std::cout << '\n';
    keep_window_open();
    return 0;
}
