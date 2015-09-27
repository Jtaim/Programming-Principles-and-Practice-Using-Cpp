//written by Jtaim
//date 26 Sept 2015
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

#include "section4.h" //custom header
void conversion(string, double, const vector<string>);

int main()
{
    double inNum{0};
    string inUnit{""};
    bool stop = false;  //loop control
    const vector<string> approved_units{"cm", "m", "in", "ft"};  // approved units
    cout << "Enter a measurement and unit.\n";
    cout << "Press | to quit.\n";
    while(!stop)
    {
        cin >> inNum;
        if(cin.eof())  // added so EOF is captured
            return 0;  // for now just just exit program
        else
        {
            cin.clear();
            cin >> inUnit;
            if(cin.eof())  // added so EOF is captured
                return 0;  // for now just just exit program
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
					conversion(inUnit, inNum, approved_units);
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
    return 0;
}
// Print the correct entries plus the coverted value for other units
// Assume conversion factors
// 1m == 100cm, 1in == 2.54cm, 1ft == 12in. Read the unitindicator into a string.
void conversion(string unit, double val, const vector<string> units)
{
    double meter = 1;
    double centimeter = 1;
    double feet = 1;
    double inch = 1;
    if(unit == "m")
    {
        meter = val;
        centimeter = meter * 100;
        inch = centimeter / 2.54;
        feet = inch / 12;
    }
    else if(unit == "cm")
    {
        centimeter = val;
        meter = centimeter / 100;
        inch = centimeter / 2.54;
        feet = inch / 12;
    }
    else if(unit == "in")
    {
        inch = val;
        feet = inch / 12;
        centimeter = inch * 2.54;
        meter = centimeter / 100;
    }
    else if(unit == "ft")
    {
        feet = val;
        inch = feet * 12;
        centimeter = inch * 2.54;
        meter = centimeter / 100;
    }
    else
        cerr << "error no such unit exists to convert.\n";
    for(string converts : units)
    {
        if(converts == "m")
            val = meter;
        else if(converts == "cm")
            val = centimeter;
        else if(converts == "ft")
            val = feet;
        else if(converts == "in")
            val = inch;
        cout << "Entered measurement is " << val << " " << converts << endl;
    }
}