//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 13.
 Create a program to find all the prime numbers between 1 and 100.
 There is a classic method for doing this, called the “Sieve of Eratosthenes.”
 If you don’t know that method, get on the web and look it up. Write your program using this method.
 https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
*/

#include "section4.hpp"

int main()
{
    std::size_t constexpr max{ 100 };

    // build table
    std::vector<bool> sieve( max, true );

    // set first 2 elements representing 0 and 1 to false as not prime
    sieve[0] = sieve[1] = false;

    for( std::size_t i{}; i < sieve.size(); ++i )
    {
        if( sieve[i] == true )
        {
            for( std::size_t j{ 2 }; ( j * i ) < sieve.size(); ++j )
            {
                sieve[i * j] = false;
            }
        }
    }

    // print out the prime numbers
    for( std::size_t columnSize{ 1 }, index{}; index != sieve.size(); ++index )
    {
        //10 columns 
        if( sieve[index] == true )
        {
            std::cout << index << ( columnSize % 10 != 0 ? '\t' : '\n' );
            ++columnSize;
        }
    }

    std::cout << std::endl;
    keep_window_open();
    return 0;
}
