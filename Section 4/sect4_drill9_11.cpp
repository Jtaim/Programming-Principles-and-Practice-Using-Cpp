//written by Jtaim
//date 26 Sept 2015
//updated 13 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 9 - 11.
1. Write a program that consists of a while-loop that (each time around the loop)
   reads in two int numbers and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
   numbers and the larger value is: followed by the larger value.
3. Augment the program so that it writes the line the numbers are equal (only) if 
   they are equal.
4. Change the program so that it uses double instead of int.
5. Change the program so that it writes out the numbers are almost equal after writing
   out which is the larger and the smaller if the two numbers differ by less than 1.0 / 100.
6. Now change the body of the loop so that it reads just one double each time around.
   Define two variables to keep track of which is the smallest and which is the largest
   value you have seen so far. Each time through the loop write out the value entered.
   If it’s the smallest so far, write the smallest so far after the number.
   If it is the largest so far, write the largest so far after the number.
7. Add a unit to each double entered; that is, enter values such as 10cm, 2.5in, 5ft, 
   or 3.33m. Accept the four units: cm, m, in, ft. Assume conversion factors
   1m == 100cm, 1in == 2.54cm, 1ft == 12in. Read the unit indicator into a string.
   You may consider 12 m (with a space between the number and the unit) equivalent to 12m (without a space).
8. Reject values without units or with “illegal” representations of units, 
   such as y, yard, meter, km, and gallons.
9. Keep track of the sum of values entered (as well as the smallest and the largest)
   and the number of values entered. When the loop ends, print the smallest, the largest,
   the number of values, and the sum of values. Note that to keep the sum, you have to
   decide on a unit to use for that sum; use meters.
10.Keep all the values entered (converted into meters) in a vector.
   At the end, write out those values.
11.Before writing out the values from the vector, sort them (that’ll make them come out
   in increasing order).
*/

#include "section4.h"	//custom header
#include <vector>
#include <string>
#include <algorithm>

double convert_meter(double, const std::string&);

int main()
{
	using std::cout;
	using std::cin;
	// termination character
	const char TERMINATION_VALUE = '|';
	// approved units
	const std::vector<std::string> APPROVED_UNITS{ "cm", "m", "in", "ft" };
	// tolerance to determine numbers are close enough to be equal
	constexpr double TOLERANCE = 1.0 / 1000;

	double in_num = 0;
	std::string in_unit;
	double temp_num = 0;
	std::vector<double> entered_values{};
	double small = 0;
	double large = 0;
	double sum = 0;

	bool exit = false;	//loop control
	while (!exit)
	{
		cout << "Enter a number with unit of measure (cm, m, in, ft).\n";
		cout << "Press | to quit.\n";
		in_num = 0;
		in_unit = "";
		temp_num = 0;
		// checks if user entered a zero
		// will let fall through if entered units with out a number
		while (cin >> in_num)
		{
			if (in_num == 0)
			{
				cout << "Can not convert zero to anything, try again.\n";
				// clear out everything in buffer
				cin.clear();
				cin.ignore(32768, '\n');
			}
			else
			{
				break;
			}
		}
		// clear error to get units
		cin.clear();
		cin >> in_unit;
		//check for termination character
		if (in_unit.find_first_of(TERMINATION_VALUE) != std::string::npos)
		{
			cout << "Show summary of data entered\n";
			exit = true;
		}
		else
		{
			// check for valid unit of measure
			if (find(begin(APPROVED_UNITS), end(APPROVED_UNITS), in_unit) != end(APPROVED_UNITS))
			{
				// got a good unit but no number assume input is 1
				if (in_num == 0)
				{
					in_num = 1.0;
				}
				temp_num = convert_meter(in_num, in_unit);
				// if sum == 0 means this is first number entered
				if (sum == 0)
				{
					small = large = temp_num;
					cout << "This is the smallest number entered so far!\n";
					cout << "This is the largest number entered so far!\n\n";
				}
				// check for new small number
				else if ((temp_num - small) < 0 && fabs(temp_num - small) > TOLERANCE)
				{
					small = temp_num;
					cout << "This is the smallest number entered so far!\n\n";
				}
				// check for new large number
				else if ((temp_num - large) > 0 && fabs(temp_num - large) > TOLERANCE)
				{
					large = temp_num;
					cout << "This is the largest number entered so far!\n\n";
				}
				sum += temp_num;
				entered_values.push_back(temp_num);
			}
			else
			{
				cout << "Unexpected unit of measurement, try again.\n\n";
			}
		}
	}
	cout << small << "m was the smallest number entered.\n";
	cout << large << "m was the largest number entered.\n";
	cout << sum << "m was the sum of all the numbers entered.\n\n";
	sort(entered_values.begin(), entered_values.end());
	cout << "All numbers entered where:\n";
	for (double i : entered_values)
	{
		cout << i << "m\n";
	}
	keep_window_open();
	return 0;
}
// Assume conversion factors
// 1m == 100cm, 1in == 2.54cm, 1ft == 12in.
double convert_meter(double val, const std::string& unit)
{
	if (unit == "cm")
		val /= 100;
	if (unit == "m")	//put all units in units of meters (m)
		val *= 1.0;
	if (unit == "in")
		val = val*2.54 / 100;
	if (unit == "ft")
		val = val * 12 * 2.54 / 100;
	return val;
}
