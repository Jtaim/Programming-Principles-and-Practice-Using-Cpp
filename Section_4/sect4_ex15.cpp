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
    // set first known prime of 2
    std::vector<int> primes{ 2 };
    unsigned numOfPrimes{ 0U };

    std::cout << "enter number of primes you want to find." << std::endl;
    if (!(std::cin >> numOfPrimes)) {
        simple_error("entered invalid integer value\n");
    }

    unsigned count{ 1U };   // keep track of primes found, no 2 is a prime
    unsigned i{ 3U };       // set first number to see if divides

    // loop to found n primes.  already have 2 as prime.
    while (count < numOfPrimes) {
        bool isPrime = true;
        // find if prime and add to prime vector if so.
        for (auto prime : primes) {
            if (i % prime == 0) {
                isPrime = false;  // not a prime
                break;
            }
        }
        if (isPrime) {
            primes.push_back(i);  // found prime add to vector
            ++count;
        }
        ++i;
    }

    // print out the prime numbers
    int j = 1;
    for (auto x : primes) {
        //10 per row
        if (j % 10) {
            std::cout << x << '\t';
        }
        else {
            std::cout << x << std::endl;
        }
        j++;
    }

    std::cout << std::endl;
    keep_window_open();
    return 0;
}
