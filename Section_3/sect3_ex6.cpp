// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 6.
A program that prompts the user to enter three integer values, 
and then outputs the values in numerical sequence separated by commas. 
So, if the user enters the values 10 4 6, the output should be 4, 6, 10. 
If two values are the same, they should just be ordered together. 
So, the input 4 5 4 should give 4, 4, 5.
*/

#include "section3.h" //custom header

int main()
{
	using namespace std;

	cout << "A program that prompts the user to enter three integer values,\n"
		 << "and then outputs the values in numerical sequence separated by commas.\n\n"
		 << "Enter three integer values:\n";
	int val1{ 0 };
	int val2{ 0 };
	int val3{ 0 };
	if (!(cin >> val1 >> val2 >> val3)) { simple_error("Invalide entry"); }

	int min{ 0 };
	int mid{ 0 };
	int max{ 0 };
	if ((val1 <= val2) && (val1 <= val3))
	{
		if (val2 <= val3)
		{
			min = val1;
			mid = val2;
			max = val3;
		}
		else
		{
			min = val1;
			mid = val3;
			max = val2;
		}
	}
	else if ((val2 <= val1) && (val2 <= val3))
	{
		if (val1 <= val3)
		{
			min = val2;
			mid = val1;
			max = val3;
		}
		else
		{
			min = val2;
			mid = val3;
			max = val1;
		}
	}
	else
	{
		if (val1 <= val2)
		{
			min = val3;
			mid = val1;
			max = val2;
		}
		else
		{
			min = val3;
			mid = val2;
			max = val1;
		}
	}
	cout << min << ", " << mid << ", " << max << endl;
	keep_window_open();
	return 0;
}
