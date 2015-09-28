//written by Jtaim
//date 26 Sept 2015
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

#include "section4.h" //custom header
double convert_meter(string, double);

int main()
{
    double inNum{0};
    string inUnit{""};
	vector<double> entered_values{};
	double small = 0;
	double large = 0;
	const double tol = 1.0 / 1000;  //close enough
	double sum = 0;
    bool stop = false;  //loop control
    const vector<string> approved_units{"cm", "m", "in", "ft"};  // approved units
    cout << "Enter a number with unit of measure (cm, m, in, ft).\n";
    cout << "Press | to quit.\n";
    while(!stop)
    {
        cin >> inNum;
        if(cin.eof())  // added so EOF is captured
            return 0;  // for now just exit program
        else
        {
            cin.clear();
            cin >> inUnit;
            if(cin.eof())  // added so EOF is captured
                return 0;  // for now just exit program
            else if(inUnit == "|")
                stop = true;
            else if(inNum == 0)  //make sure we have a measurement before a unit
            {
                cout << "Enter a measurement before the unit.\n";
            }
            else
            {
                bool good_unit = false;  // check for valid unit
                for(string comp : approved_units)
                {
                    if(comp == inUnit)
                    {
                        good_unit = true;
                        break;  // if found exit the for loop
                    }
                    else
                        good_unit = false;
                }
				if (good_unit)
				{
					double temp = convert_meter(inUnit, inNum);
					sum += temp;
					if (temp < small || temp > large)  // check if have new smaller or larger value
					{
						if (((temp - small) < 0 && fabs(temp - small) > tol) || small == 0)
						{
							small = temp;
							cout << " This is the smallest number entered so far!\n\n";
						}
						if (((temp - large) > 0 && fabs(temp - large) > tol) || large == 0)
						{
							large = temp;
							cout << " This is the largest number entered so far!\n\n";
						}
					}
					entered_values.push_back(temp);
					inNum = 0;
					inUnit = {""};
				}
				else
				{
					cout << "Unexpected unit of measurement.\n";
					inNum = 0;
					inUnit = {""};
				}
            }
        }
    }
	inUnit = "m";
	cout << small << inUnit << " was the smallest number entered.\n";
	cout << large << inUnit << " was the largest number entered.\n";
	cout << sum << inUnit << " was the sum of all the numbers entered.\n\n";
	sort(entered_values.begin(),entered_values.end());
	for (double i : entered_values)
		cout << i << inUnit << endl;
	keep_window_open();
    return 0;
}
// Assume conversion factors
// 1m == 100cm, 1in == 2.54cm, 1ft == 12in.
double convert_meter(string unit, double val)
{
    if (unit == "cm")
		val /= 100;
	if (unit == "m")			//put all units in units of meters (m)
		val *= 1.0;
	if (unit == "in")
		val = val*2.54 / 100;
	if (unit == "ft")
		val = val * 12 * 2.54 / 100;
	return val;
}