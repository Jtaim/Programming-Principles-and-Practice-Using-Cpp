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

#include "section4.h"

int main()
{
    unsigned const max{ 100U };

    // build table
    std::vector<bool> sieve(max, true);
    using type = decltype(sieve.size());
    std::vector<type> primes{ 2 };

    for (type i = 2; i < sieve.size(); ) {
        bool done = true;
        //mark all multiples
        for (type j = 2; (j * i) < sieve.size(); ++j) {
            sieve[i * j] = false;
        }
        //find next prime
        for (type k = i + 1; k < sieve.size(); ++k) {
            if (sieve[k]) {
                i = k;
                done = false;
                primes.push_back(k);
                break;
            }
        }
        if (done) {
            break;
        }
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
