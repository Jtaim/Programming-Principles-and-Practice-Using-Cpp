//written by Jtaim
//date 8 Oct 2015
//updated 17 Dec 2016
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

#include "section4.h" // custom header
#include <vector>

int main()
{
	using std::cout;

	const int MAX = 100;

	// set first known prime
	std::vector<int> primes{ 2 };

	// start with 3 know 2 is prime
	for (int i = 3; i <= MAX; i++)
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
