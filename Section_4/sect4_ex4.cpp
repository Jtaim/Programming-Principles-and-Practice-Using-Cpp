//written by Jtaim
//date 31 Mar 2017
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
	using namespace std;

	auto constexpr max = 100;      // maximum number can select
	auto constexpr min = 1;        // minimum number can guess
	auto constexpr max_guess = 7;  // maximum number of times to ask before identifying the number

	auto choice{ '?' };
	auto high = max;					// keeps track of a new high
	auto low = min;						// keeps track of a new low
	auto guess = (high - low) / 2 + low;// keeps track of the next guess
	auto mguess{ 0 };					// keeps count of guess count
	cout << "Pick a number between " << low << " and " << high << " and let me try to guess it by asking some questions.\n";
	auto exit{ false };
	while (!exit && mguess < max_guess) {
		cout << "Is your number <= " << guess << " (y or n)? ";
		if (cin >> choice) {
			choice = static_cast<decltype(choice)>(tolower(choice));
			if (choice == 'y' || choice == 'n') {
				mguess++;
				if (choice == 'y') {
					high = guess;
				}
				else if (choice == 'n') {
					low = guess + 1;
				}
				if (high == low) {
					cout << "Found the answer " << high << " in " << mguess << " guesses.\n";
					exit = true;
				}
				else {
					guess = (high - low) / 2 + low;
				}
			}
			else {
				cout << "You did not pick a valid (y or n) answer.  Select again.\n";
			}
		}
		else {
			cin.clear();
			exit = true;
		}
	}
	if (high != low) {
		simple_error("Exceeded max number of guesses\n");
	}
	keep_window_open();
	return 0;
}
