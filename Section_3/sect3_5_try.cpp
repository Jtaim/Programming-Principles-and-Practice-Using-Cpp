//written by Jtaim
//date 23 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3.5 try this exercise
*/

#include "section3.h" //custom header

int main()
{
	using namespace std;

	string previous = "";
	string current;
	cout << "A program to check for repeating words. EOF or ctrl-z to exit\n";
	cout << "Enter a sentance to check: ";
	while (cin >> current)
	{
		if (current.size() == previous.size())
		{
			// what if word is repeated but one is capitalized?
			int i = 0;
			while (i < current.size())
			{
				if (tolower(current[i]) != tolower(previous[i])) { break; }
				++i;
			}
			if (i == current.size())
			{
				cout << "repeated word: " << current << endl;
			}
			else { previous = current; }
		}
		else { previous = current; }
	}
	return 0;
}