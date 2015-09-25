//written by James Weiland
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 4. 
A program to play a numbers guessing game. 
The user thinks of a number between 1 and 100 and your program asks questions to figure out what the number is 
(e.g., “Is the number you are thinking of less than 50?”). 
Your program should be able to identify the number after asking no more than seven questions. 
Hint: Use the < and <= operators and the if-else construct.
*/

#include "std_lib_facilities.h" 							// custom header
int const MAX = 100;										// maximum number can select
int const MIN = 1;											// minimum number can guess
int const MAX_GUESS = 7;									// maximum number of times to ask before identifying the number

int main()
try
{
	char choice = 'n';
	int guess = (MAX-MIN)/2;								// keeps track of the next guess
//*******************************************************************************************************************************************************
	for(int iteration=MIN;iteration<=MAX;iteration++) {	// for loop to debug all combinations
//*******************************************************************************************************************************************************
	int high = MAX;											// keeps track of a new high
	int low = MIN;											// keeps track of a new low
	int mguess = MAX_GUESS;  								// keeps count of guess count
	//cout << "Pick a number between " << low << " and " << high << " and let me try to guess it by asking some questions." << endl;
	while(mguess>=0) {										// runs until maximum guess is zero
		mguess--;
		guess = (high-low)/2 + low;
		//cout << "Is your number <= " << guess << " (y or n)? ";    // ask for user input
		//cin >> choice;									// user input 
//*******************************************************************************************************************************************************
		if(iteration<=guess) choice = 'y';    // added the if statement for debug to auto give yes or no
		else if(iteration>guess) choice = 'n';
		//cout << "Is " << iteration << " <= " << guess << " " << choice << '\t';
//********************************************************************************************************************************************************
		if(choice=='y' || choice=='Y') {
			high = guess;			// update high value
		}
		else if(choice=='n' || choice=='N') {
			low = guess+1;			// update low value
		}
		else {						// gives user option to select correct response yes or no
			cout << "You did not pick a valid (y or n) answer.  Select again." << endl;
			continue;
		}
//*******************************************************************************************************************************************************
		//cout << "high == " << high << '\t' << "low == " << low << endl;   // for debug
//*******************************************************************************************************************************************************
		if(high==low) {				// found the value
			break;
		}
	}
	if(mguess<0) {					//flag an error if exceed max number of guesses
		error("dumb computer"); 
//*******************************************************************************************************************************************************		
		//cout << "error cycle " << "\t\tIteration " << iteration << " failed" << endl;    // for debug
//*******************************************************************************************************************************************************
		}
//*******************************************************************************************************************************************************
	else    // else is used with the above for statement to display each iteration
		if(iteration==high)
			cout << "Iteration " << iteration << "\tpassed"  << "\tcycle " << (MAX_GUESS-mguess) <<endl;
		else
			cout << "Iteration " << iteration << "\t<failed>"  << "\tcycle " << (MAX_GUESS-mguess) <<endl;
	}
//*******************************************************************************************************************************************************
	//cout << "The answer is " << high << endl;   //could have picked low also (high == low)
	return 0;
}

catch (runtime_error e) {
	// this code is to produce error messages; it will be described in Chapter 5
	cout << e.what() << endl;
}
catch (...) {
	// this code is to produce error messages; it will be described in Chapter 5
	cout << "exiting\n";
}