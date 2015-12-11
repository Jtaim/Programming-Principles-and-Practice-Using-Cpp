//Written by Jtaim
//Date 9 Dec 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 10
Ask user for 2 numbers.
Ask if want to do permutation or combination
p(a,b) = a!/(a-b)!
c(a,b) = p(a,b)/b!
*/

#include "section6.h"


int get_integer()  // get valid integers from user
{
	int x = 0;
	if (cin >> x) {
		return x;
	}
	else
		error("Invalid number entry.\n");
}

char perm_or_comb() // check for valid input from user for selection of permutation or combination
{
	char pc = '?';
	cin >> pc;
	pc = tolower(pc);
	if (pc == 'p' || pc == 'c') {
		return pc;
	}
	else
		error("Invalid permutation or combination entry.\n");
}

int factoral(int start, int end)  // do factorial to a selected stop
{
	int fact = 1;
	for (auto i = start; i > (start-end); --i) {
		fact *= i;
		if ((i > 0) && (fact > INT_MAX - i)) {
			error("int overflow error");
		}
		if ((i < 0) && (fact < INT_MAX - i)) {
			error("int overflow error");
		}
	}
	return fact;
}

int permutation(int a, int b)
{
	if (a <= 0 || (a - b) < 0)
		error("Negative term in the permutation.\n");
	return factoral(a,b);
}

int combination(int a, int b)
{
	int c;
	c = permutation(a, b)/factoral(b,b);
	return c;
}

int main()
try
{
	cout << "Enter 2 numbers\n";
	int a = 0;
	int b = 0;
	a = get_integer();
	b = get_integer();
	cout << "Do you want to do a permutation (p) or combination (c)?\n";
	char p_c;
	p_c = perm_or_comb();
	int answer = 0;
	if (p_c == 'p') {
		answer = permutation(a,b);
	}
	else {
		answer = combination(a, b);
	}
	cout << "The " << (p_c == 'p' ? "permutation" : "combination") << " is " << answer << ".\n";

	keep_window_open();
	return 0;
}
catch (exception& e) 
{
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) 
{
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}