//written by Jtaim
//date 11 Oct 2015
//updated 18 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 16. 
A program that finds the mode of a set of positive integers
The "mode" is the value that occurs most often. 
If no number is repeated, then there is no mode for the list.
Refer to drill 3
*/

#include "section4.h"
#include <vector>
#include <algorithm>

int main()
{
	using std::cout;
	using std::cin;

	std::vector<int> pos_ints{};  // hold numbers to check mode
	int n = -1;
	cout << "Enter a set of positive integers so can find the MODE. (use any non number to exit)\n";
	bool exit = false;
	while (!exit)
	{
		while ((cin >> n) && n > 0)
		{
			pos_ints.push_back(n);
		}
		if (!cin.good())
		{
			exit = true;
			break;
		}
		else
		{
			cout << "entered an invalid number or < 0.\n";
			cin.clear();
			cin.ignore(32768, ' ');
		}
	}
	if (!pos_ints.empty())
	{
		std::sort(pos_ints.begin(), pos_ints.end());
		int count = 0;
		int new_count = 0;
		int temp = -1;
		int mode = 0;
		for (auto x : pos_ints)
		{
			if (x == temp || temp == -1)
			{
				++new_count;
				temp = x;
				if (new_count >= count)
				{
					mode = x;
					count = new_count;
				}
			}
			else
			{
				new_count = 1;
				temp = x;
			}
		}
		// print out the MODE
		if (count > 1)
		{
			cout << "The MODE of entered integers is " << mode << ".\n";
			cout << mode << " was found " << count << " times.\n";
		}
		else
		{
			cout << "There is no MODE from this set.\n";
		}
		cout << "The sorted entered numbers:\n";
		int j = 1;
		// print out the entered numbers
		for (auto x : pos_ints)
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
	}
	else
	{
		simple_error("nothing entered\n");
	}
	cout << '\n';
	keep_window_open();
	return 0;
}
