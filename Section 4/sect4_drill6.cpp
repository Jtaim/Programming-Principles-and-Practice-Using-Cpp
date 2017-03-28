//written by Jtaim
//date 27 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 6.
1. Write a program that consists of a while-loop that (each time around the loop)
   reads in two int numbers and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
   numbers and the larger value is: followed by the larger value.
3. Augment the program so that it writes the line the numbers are equal (only) if they are equal.
4. Change the program so that it uses double instead of int.
5. Change the program so that it writes out the numbers are almost equal after writing
   out which is the larger and the smaller if the two numbers differ by less than 1.0 / 100.
6. Now change the body of the loop so that it reads just one double each time around.
   Define two variables to keep track of which is the smallest and which is the largest
   value you have seen so far. Each time through the loop write out the value entered.
   If it’s the smallest so far, write the smallest so far after the number.
   If it is the largest so far, write the largest so far after the number.
*/

#include "section4.h"	//custom header

int main()
{
	using namespace std;
	const char terminationChar = '|';	//termination character
	const int howMany = 1;				//numbers to get per loop iteration
	const double tolerance = 1.0 / 100;	//close enough for floating point comparison


	double enteredNumber;
	vector<decltype(enteredNumber)> enteredNumbers;
	bool stop{ false };
	while (!stop)
	{
		cout << "Enter a number. Enter " << terminationChar << " to exit.\n";
		for (int itr = 0; itr < howMany; ++itr)
		{
			if (cin >> enteredNumber) {
				enteredNumbers.push_back(enteredNumber);
			}
			else {	//check for valid termination
				cin.clear();	//clear cin errors
				char c;
				cin >> c;
				if (c == terminationChar) {
					enteredNumbers.clear();
					stop = true;
					break;
				}
				else {
					simple_error("invalid number entry");
				}
			}
		}
		// print numbers if valid
		if (enteredNumbers.size() > 0) {
			cout << "value entered: " << enteredNumber << endl;
			//sort will place largest at end and smallest at begin.
			sort(enteredNumbers.begin(), enteredNumbers.end());
			//first entry so is smallest and largest
			if (enteredNumbers.size() == 1) {
				cout << enteredNumber << " is the smallest so far\n";
				cout << enteredNumber << " is the largest so far\n\n";
			}
			//check for new smallest
			else if (enteredNumbers.front() == enteredNumber) {
				cout << enteredNumber << " is the smallest so far\n";
			}
			//check for new largest
			else if (enteredNumbers.back() == enteredNumber) {
				cout << enteredNumber << " is the largest so far\n\n";
			}
			//the else is optional :)
			else { continue; }
		}
	}
	cout << "Bye\n";
	keep_window_open();
	return 0;
}
