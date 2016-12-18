//written by Jtaim
//date 9 Oct 2015
//updated 17 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 12. 
 Modify the program described in the previous exercise 11 to take an input value max
 and then find all prime numbers from 1 to max.
*/

#include "section4.h"
#include <vector>

int main()
{
	using std::cout;
	using std::cin;

	// set first known prime
	std::vector<int> primes{ 2 };

	int max = 0;
	cout << "enter number that want to find all primes up to it.\n";
	while (!(cin >> max))
	{
		cout << "entered an invalid number.\n";
		cin.clear();
		cin.ignore(32768, '\n');
	}
	// start with 3 know 2 is prime
	for (int i = 3; i <= max; i++)
	{
		bool is_prime = true;
		// find if prime and add to prime vector if so.
		for (auto prime : primes)
		{
			if (i % prime == 0)
			{
				is_prime = false;  // not a prime
				break;
			}
		}
		if (is_prime)
		{
			primes.push_back(i);
		}
	}
	int j = 1;
	// print out the prime numbers
	for (auto x : primes)
	{
		//10 per row
		if (j % 10)
		{
			cout << x << '\t';
		}
		else
		{
			cout << x << '\n';
		}
		j++;
	}
	cout << '\n';
	keep_window_open();
	return 0;
}
