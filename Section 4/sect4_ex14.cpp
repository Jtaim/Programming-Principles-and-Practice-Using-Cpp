//written by Jtaim
//date 10 Oct 2015
//updated 17 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 14. 
 Modify exercise 13 to take an input value max and then find all prime numbers from 1 to max.
*/

#include "section4.h"
#include <vector>

int main()
{
	using std::cout;
	using std::cin;

	cout << "enter number that want to find all primes up to it.\n";
	int max = 0;
	while (!(cin >> max))
	{
		cout << "entered an invalid number.\n";
		cin.clear();
		cin.ignore(32768, '\n');
	}
	// build table
	std::vector<bool> sieve(max, true);

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
