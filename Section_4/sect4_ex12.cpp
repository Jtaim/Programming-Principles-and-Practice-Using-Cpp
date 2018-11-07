//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
 Section 4 exercise 12.
 Modify the program described in the previous exercise 11 to take an input value max
 and then find all prime numbers from 1 to max.
*/

#include "section4.h"

int main()
{
    // set first known prime
    std::vector<int> primes{ 2 };

    auto max{ 0 };
    std::cout << "enter number that want to find all primes up to it." << std::endl;
    if (!(std::cin >> max)) {
        simple_error("entered invalid integer value\n");
    }

    // start with 3
    for (int i = 3; i <= max; i++) {
        bool is_prime = true;
        // find if prime and add to prime vector if so.
        for (auto prime : primes) {
            if (i % prime == 0) {
                is_prime = false;  // not a prime
                break;
            }
        }
        if (is_prime) {
            primes.push_back(i);
        }
    }

    int j = 1;
    // print out the prime numbers
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
