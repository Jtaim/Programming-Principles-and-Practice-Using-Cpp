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
	using std::cout;
	using std::cin;

	std::vector<int> primes{ 2 };  // set first known prime of 2
	auto num_of_primes{ 0U };
	cout << "enter number of primes you want to find.\n";
	if (!(cin >> num_of_primes)) {
		simple_error("entered invalid int\n");
	}
	auto count{ 1U }; // keep track of primes found, no 2 is a prime
	auto i{ 3U };
	// loop to found n primes.  already have 2 as prime.
	while (count < num_of_primes) {
		bool is_prime = true;
		// find if prime and add to prime vector if so.
		for (auto prime : primes) {
			if (i % prime == 0) {
				is_prime = false;  // not a prime
				break;
			}
		}
		if (is_prime) {
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
			cout << x << '\t';
		}
		else {
			cout << x << '\n';
		}
		j++;
	}
	cout << '\n';
	keep_window_open();
	return 0;
}
