//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.5.1
Implement square() without using the multiplication operator; 
that is, do the x*x by repeated addition (start a variable result at 0 and add x to it x times). 
Then run some version of “the first program” using that square().
*/

#include "section4.h" //custom header

// function declaration
int square(int);

int main()
{
	using namespace std;
	cout << "Program to find the squared results as the first program did in 1949.\n";
	for (int num = 0; num < 100; ++num) {
		cout << num << "\tsquared =\t" << square(num) << endl;
	}
	keep_window_open();
	return 0;
}

// do repeat addition not multiplication function
int square(int i)
{
	int result{ 0 };
	for (int j = 0; j < i; j++) { result += i; }
	return result;
}
