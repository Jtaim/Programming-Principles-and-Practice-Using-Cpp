//written by Jtaim
//date 26 Sept 2015
//updated 12 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 7 and 8.
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
*/

#include "section4.h"	//custom header
#include <vector>
#include <string>
#include <algorithm>

void conversion(std::string&, double, const std::vector<std::string>&);

int main()
{
	using std::cout;
	using std::cin;
	// termination character
	const char TERMINATION_VALUE = '|';
	// approved units
	const std::vector<std::string> APPROVED_UNITS{ "cm", "m", "in", "ft" };

	bool exit = false;	//loop control
	while (!exit)
	{
		cout << "Enter a number with unit of measure (cm, m, in, ft).\n";
		cout << "Press | to quit.\n";
		double in_num{ 0 };
		std::string in_unit;
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
			cout << "Program terminated\n";
			exit = true;
		}
		else
		{
			// check for valid unit of measure
			if (find(begin(APPROVED_UNITS), end(APPROVED_UNITS), in_unit) != end(APPROVED_UNITS))
			{
				//got a good unit but no number assume input is 1
				if (in_num == 0)
				{
					in_num = 1.0;
				}
				conversion(in_unit, in_num, APPROVED_UNITS);
			}
			else
			{
				cout << "Unexpected unit of measurement, try again.\n\n";
			}
		}

	}
	cout << "Bye\n";
	keep_window_open();
	return 0;
}
// Print the correct entries plus the converted value for other units
// Assume conversion factors
// 1m == 100cm, 1in == 2.54cm, 1ft == 12in. Read the unit indicator into a string.
void conversion(std::string& unit, double val, const std::vector<std::string>& units)
{
	double meter = 1;
	double centimeter = 1;
	double feet = 1;
	double inch = 1;
	if (unit == "m")
	{
		meter = val;
		centimeter = meter * 100;
		inch = centimeter / 2.54;
		feet = inch / 12;
	}
	else if (unit == "cm")
	{
		centimeter = val;
		meter = centimeter / 100;
		inch = centimeter / 2.54;
		feet = inch / 12;
	}
	else if (unit == "in")
	{
		inch = val;
		feet = inch / 12;
		centimeter = inch * 2.54;
		meter = centimeter / 100;
	}
	else if (unit == "ft")
	{
		feet = val;
		inch = feet * 12;
		centimeter = inch * 2.54;
		meter = centimeter / 100;
	}
	else
		simple_error("no such unit exists to convert.\n");
	for (std::string converts : units)
	{
		if (converts == "m")
			val = meter;
		else if (converts == "cm")
			val = centimeter;
		else if (converts == "ft")
			val = feet;
		else if (converts == "in")
			val = inch;
		std::cout << "Entered measurement is " << val << converts << std::endl;
	}
	std::cout << std::endl;
}
