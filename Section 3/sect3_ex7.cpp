// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 7.
Do exercise 6, but with three string values. So, if the user enters 
the values Steinbeck, Hemingway, Fitzgerald, the output should be 
Fitzgerald, Hemingway, Steinbeck.
*/

#include "section3.h" //custom header

int main()
{
	using namespace std;

	cout << "Enter 3 words and output will place in alphebetic order.\n\n";
	cout << "Enter three words:\n";
	string val1{ "???" };
	string val2{ "???" };
	string val3{ "???" };
	cin >> val1 >> val2 >> val3;

	string min{ "???" };
	string mid{ "???" };
	string max{ "???" };
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
