//written by Jtaim
//date 1 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 6. 
Make a vector holding the ten string values "zero", "one", . . . "nine". 
Use that in a program that converts a digit to its corresponding spelled-out value; e.g., the input 7 gives the output seven. 
Have the same program, using the same input loop, convert spelled-out numbers into their digit form; e.g., the input seven gives the output 7.
*/

#include "section4.h"  // custom header

const vector<string> numbers{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main()
{
	while(true)
	{
		int nVal = -1;
		cout << "enter a number between 0 and 9: \n";
		cin >> nVal;
		if (cin.eof()) {
			cin.clear();
			//cin.ignore(INT_MAX, '\n');
			cout << "eof found!\n";
			break;
		}
		else if (cin.fail()) { // invalid nonINT entry. check if correct spelled out
			cin.clear();  // clear cin error flags so can accept new data
			string sVal{ "??" };
			cin >> sVal;
			for (decltype(sVal.length()) i = 0; i < sVal.length(); ++i) { // set string to lower case
				sVal[i] = tolower(sVal[i]);
			}
			for (decltype(numbers.size()) i = 0; i < numbers.size(); ++i) {
				if (sVal == numbers[i]) {
					nVal = i; // enter index as the number value
					break;  // match found break from for loop
				}
			}
		}
		if(nVal >= 0 && nVal < numbers.size()) {
			cout << nVal << " is " << numbers[nVal] << endl;
		}
		else {
			cout << "Number entered must be between 0 and 9.\n";
		}
	}
    keep_window_open();
	return 0;
}
	