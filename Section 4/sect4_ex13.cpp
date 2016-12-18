//written by Jtaim
//date 9 Oct 2015
//updated 17 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 13. 
 Create a program to find all the prime numbers between 1 and 100. 
 There is a classic method for doing this, called the “Sieve of Eratosthenes.” 
 If you don’t know that method, get on the web and look it up. Write your program using this method.
 https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
*/

#include "section4.h"
#include <vector>

int main()
{
	using std::cout;

	const int MAX = 100;

	// build table
	std::vector<bool> sieve(MAX, true);

	typedef decltype(sieve.size()) type;
	std::vector<type> primes{ 2 };

	for (type i = 2; i < sieve.size(); )
	{
		bool done = true;
		//mark all multiples
		for (type j = 2; (j * i) < sieve.size(); ++j)
		{
			sieve[i * j] = false;
		}
		//find next prime
		for (type k = i + 1; k < sieve.size(); ++k)
		{
			if (sieve[k])
			{
				i = k;
				done = false;
				primes.push_back(k);
				break;
			}
		}
		if (done)
		{
			break;
		}
	}
	// print out the prime numbers
	int j = 1;
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
