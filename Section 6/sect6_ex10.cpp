//Written by Jtaim
//Date 9 Dec 2015
//updated 28 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 10
Ask user for 2 numbers.
Ask if want to do permutation or combination
p(a,b) = a!/(a-b)!
c(a,b) = p(a,b)/b!
https://www.mathsisfun.com/combinatorics/combinations-permutations.html
*/

#include "section6.h"

// get validated user input
template<typename T>
bool get_input(T& val)
{
	bool valid = false;
	while (!(std::cin >> val))
	{
		std::cout << "invalid entry. reenter\n";
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		valid = false;
	}
		valid = true;
	return valid;
}

// check for valid input from user for selection of permutation or combination
void get_selection(char& val)
{
	bool valid = false;
	do
	{
		get_input(val);
		val = static_cast<char>(std::tolower(val));
		if (val != 'p' && val != 'c')
		{
			std::cout << "Invalid permutation or combination entry.\n";
		}
		else
		{
			valid = true;
		}
	} while (!valid);
}

// do factorial to a selected stop
int factoral(int start, int end)
{
	int fact = 1;
	for (auto i = start; i > (start - end); --i)
	{
		fact *= i;
		if ((i > 0) && (fact > INT_MAX - i))
		{
			error("int overflow error");
		}
		if ((i < 0) && (fact < INT_MAX - i))
		{
			error("int overflow error");
		}
	}
	return fact;
}

int permutation(int a, int b)
{
	if (a <= 0 || (a - b) < 0)
	{
		error("Negative term in the permutation.\n");
	}
	return factoral(a, b);
}

int combination(int a, int b)
{
	int c;
	c = permutation(a, b) / factoral(b, b);
	return c;
}

int main()
{
	try
	{
		std::cout << "Enter 2 numbers\n";
		int a = 0;
		int b = 0;
		while (!(a > b))
		{
			std::cout << "'a' must be > 'b'\n";
			get_input(a);
			get_input(b);
		}
		std::cout << "Do you want to do a permutation (p) or combination (c)?\n";
		char p_c;
		get_selection(p_c);

		int answer = 0;
		if (p_c == 'p')
		{
			answer = permutation(a, b);
		}
		else if (p_c == 'c')
		{
			answer = combination(a, b);
		}
		else
		{
			error("should not get here.\n");
		}
		std::cout << "The " << (p_c == 'p' ? "permutation" : "combination") << " is " << answer << ".\n";

		keep_window_open();
		return 0;
	}
	catch (std::exception& e)
	{
		std::cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...)
	{
		std::cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
}
