//written by Jtaim
//date 25 Sept 2015
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

#include "section4.h" //custom header
bool check_input(const char);

//C++ programs start by executing the function main
int main()
{
	double enterVal = 0.0;
	double smallVal = 0.0;
	double largeVal = 0.0;
	const char termVal = '|';
	const double tolerance = 1.0 / 100;  //close enough for floating point comparison
	bool terminate = true;
	bool firstItr = true;

	while (terminate)
	{
		cout << "Enter a number. Enter " << termVal << " to exit.\n";
		if (!(cin >> enterVal))
			terminate = check_input(termVal);
		else
		{
			cout << "Number entered was " << enterVal << '.';
			if (firstItr)  // check first loop itr set small and large to that val
			{
				firstItr = false;
				cout << " This is the first number entered!\n\n";
				smallVal = enterVal;
				largeVal = enterVal;
			}
			if (enterVal < smallVal || enterVal > largeVal)  // check if have new smaller or larger value
			{
				if (enterVal < smallVal)
				{
					smallVal = enterVal;
					cout << " This is the smallest number entered so far!\n\n";
				}
				else
				{
					largeVal = enterVal;
					cout << " This is the largest number entered so far!\n\n";
				}
			}
			cout << "\n\n"; //provide newline to enter next value
		}
	}
	keep_window_open();
	return 0;
}

bool check_input(const char termVal)
{
	bool goodBad = true;
	if (cin.eof())
	{
		cin.clear();
		//cin.ignore(INT_MAX, '\n');
		cout << "EOF found\n";
		goodBad = false;
	}
	else if (cin.fail())
	{
		char x = '?';
		cin.clear();
		cin >> x;
		cin.ignore(INT_MAX, '\n');	//clear cin buffer until find new line char
		if (termVal == x)
		{
			cout << "Program terminated, detected entered " << x << " key press\n";
			goodBad = false;
		}
		else if (x == 26) // 26 = ctrl-z and  ctrl-d = 04 wonder why i need this
		{
			cout << "EOF 26 found\n";
			goodBad = false;
		}
		else
		{
			cout << "Entered value is not valid\n";
			goodBad = true;
		}
	}
	else if (cin.bad())
	{
		cin.clear();
		//cin.ignore(INT_MAX, '\n');
		cout << "unknown termination\n";
		goodBad = false;
	}
	return goodBad;
}