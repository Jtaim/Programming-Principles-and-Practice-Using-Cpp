//written by Jtaim
//date 30 Sept 2015
//date 15 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 4. 
A program to play a numbers guessing game. 
The user thinks of a number between 1 and 100 and your program asks questions to figure out what the number is 
(e.g., “Is the number you are thinking of less than 50?”). 
Your program should be able to identify the number after asking no more than seven questions. 
Hint: Use the < and <= operators and the if-else construct.
*/

#include "section4.h"

int main()
{
	using std::cout;
	using std::cin;
	using std::endl;

	int constexpr MAX = 255;      // maximum number can select
	int constexpr MIN = 1;        // minimum number can guess
	int constexpr MAX_GUESS = 7;  // maximum number of times to ask before identifying the number

	char choice{ '?' };
	int high = MAX;						// keeps track of a new high
	int low = MIN;						// keeps track of a new low
	int guess = (high - low) / 2 + low;	// keeps track of the next guess
	int mguess = 0;						// keeps count of guess count
	cout << "Pick a number between " << low << " and " << high << " and let me try to guess it by asking some questions.\n";
	bool exit = false;
	while (!exit && mguess != MAX_GUESS)
	{
		cout << "Is your number <= " << guess << " (y or n)? ";
		cin >> choice;
		if (cin.eof() || cin.bad())
		{
			cin.clear();
			exit = true;
		}
		else
		{
			choice = tolower(choice);
			if (choice == 'y' || choice == 'n')
			{
				mguess++;
				if (choice == 'y')
				{
					high = guess;		// update high value
				}
				else
				{
					low = guess + 1;	// update low value
				}
				if (high == low)
				{
					cout << "Found the answer in " << MAX_GUESS << " guesses.\n";
					exit = true;
				}
				else
				{
					guess = (high - low) / 2 + low;
				}
			}
			// gives user option to select correct response yes or no
			else
			{
				cout << "You did not pick a valid (y or n) answer.  Select again.\n";
			}
		}
	}
	if (mguess > MAX_GUESS)
	{
		cout << "Exceeded max number of guesses\n";
	}
	keep_window_open();
	return 0;
}
