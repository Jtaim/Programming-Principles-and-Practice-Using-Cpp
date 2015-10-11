//written by Jtaim
//date 9 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 12. 
 Modify the program described in the previous exercise 11 to take an input value max
 and then find all prime numbers from 1 to max.
*/

#include "section4.h" // custom header

int main()
{
	vector<int> primes {2};  // set first known prime of 2
	int max = 0;
    cout << "enter number that want to find all primes up to it.\n";
    cin >> max;
    if(cin.fail()) {
        cout << "entered an invalid number.\n";
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    }
    else {
        for(int i=3; i<=max; i++) {	// start with 3 know 2 is prime
            bool is_prime = true;
            for(auto prime : primes) { // find if prime and add to prime vector if so.
                if(i%prime==0) {
                    is_prime = false;  // not a prime
                    break;
                }
            }
            if(is_prime) {
                primes.push_back(i);
            }
        }
        int j = 1;
        for(auto x : primes) { // print out the prime numbers
            if(j%10) {  //10 per row
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