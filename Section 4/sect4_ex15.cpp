//written by Jtaim
//date 10 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 15. 
A program that takes an input value n and then finds the first n primes
*/

#include "section4.h" // custom header

int main()
{
	vector<int> primes{ 2 };  // set first known prime of 2
	int n = 1;
	cout << "enter number of primes you want to find.\n";
	cin >> n;
	if (cin.fail()  || n<=0) {
		cout << "entered an invalid number.\n";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	else {
		int count = 1; // keep track of primes found, no 2 is a prime
		int i = 3;
		while(count < n) { // loop to found n primes.  already have 2 as prime.
			bool is_prime = true;
			for (auto prime : primes) { // find if prime and add to prime vector if so.
				if (i%prime == 0) {
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
		int j = 1;
		for (auto x : primes) { // print out the prime numbers
			if (j % 10) {  //10 per row
				cout << x << '\t';
			}
			else {
				cout << x << '\n';
			}
			j++;
		}
	}
	cout << '\n';
	keep_window_open();
	return 0;
}