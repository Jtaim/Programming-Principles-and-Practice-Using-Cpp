//written by Jtaim
//date 30 Sept 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 4. 
A program to play a numbers guessing game. 
The user thinks of a number between 1 and 100 and your program asks questions to figure out what the number is 
(e.g., “Is the number you are thinking of less than 50?”). 
Your program should be able to identify the number after asking no more than seven questions. 
Hint: Use the < and <= operators and the if-else construct.
*/

#include "section4.h"     // custom header
int const MAX = 100;      // maximum number can select
int const MIN = 1;        // minimum number can guess
int const MAX_GUESS = 7;  // maximum number of times to ask before identifying the number

int main()
{
	char choice{};
	int high = MAX;           // keeps track of a new high
	int low = MIN;            // keeps track of a new low
	int guess = (MAX - MIN) / 2 + low;  // keeps track of the next guess
	int mguess = MAX_GUESS;   // keeps count of guess count
	cout << "Pick a number between " << low << " and " << high << " and let me try to guess it by asking some questions.\n";
	cout << "Is your number <= " << guess << " (y or n)? ";  // ask for user input
	while(cin >> choice && mguess > 0)  // runs until maximum guess is zero
	{
		choice = tolower(choice);
		if(choice=='y' || choice=='n')
		{
			mguess--;  // decrement here to not include invalid yes now answer
			if (choice == 'y')
				high = guess;  // update high value
			else
				low = guess+1;  // update low value
		}
		else  // gives user option to select correct response yes or no
		{
			cout << "You did not pick a valid (y or n) answer.  Select again.\n";
		}
		if(high==low)  // found the value
			break;
		else
		{
			guess = (high - low) / 2 + low;
			cout << "Is your number <= " << guess << " (y or n)? ";  // ask for user input
		}
	}
	if (cin.eof())  // EOF is captured
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "eof found\n";
	}
	else
	{
		if (high == low)
			cout << "The answer is " << high << endl;  //could have picked low also (high == low)
		else
			cerr << "exceeded max number of guesses\n";  //exceed max number of guesses
	}
	keep_window_open();
	return 0;
}