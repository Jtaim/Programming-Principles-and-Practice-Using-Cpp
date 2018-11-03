//written by Jtaim
//date 29 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 11.
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

int main()
{
    using namespace std;
    const char terminationChar = '|';	//termination character
    const string convetToUnit{ "m" };
    const vector<pair<string, double>> convert{
        { "m", 1.0 },			//leave as is
        { "cm", 1.0 / 100 },		//convert to m
        { "in", 2.54 / 100 },		//convert to m
        { "ft", 12.0*2.54 / 100 }	//convert to m
    };

    double enteredNumber{ 0.0 };
    string unit;
    double sum{ 0.0 };
    vector<pair<double, string>> enteredMeasurements;
    bool stop{ false };
    while (!stop)
    {
        cout << "Enter a number with unit of measurement. Enter " << terminationChar << " to exit.\n";
        while (!stop)
        {
            // get number
            if ((cin >> enteredNumber)) {
                // get unit of measure
                if (enteredNumber > 0) {
                    cin >> unit;
                    // look for termination char
                    if (unit.find(terminationChar) != string::npos) {
                        cout << "termination '" << terminationChar << "' found\n";
                        stop = true;
                        break;
                    }
                    // check for valid unit of measure and convert
                    else {
                        auto i = convert.begin();
                        for (; i < convert.end(); ++i) {
                            //valid unit finds correct index into the vector convert 
                            if (i->first == unit) {
                                //cout << enteredNumber << unit << " converts to ";
                                enteredNumber *= i->second;
                                //cout << enteredNumber << convetToUnit << endl;
                                enteredMeasurements.push_back({ enteredNumber, convetToUnit });
                                sum += enteredNumber;
                                break;
                            }
                        }
                        if (i == convert.end()) {
                            cout << "illegal units. Measurement was discarded.\n";
                        }
                    }
                }
                else {
                    cin.clear();			//clear cin error if is one
                    cin.ignore(256, '\n');	//clear all entries until new line is found
                    cout << "can not enter a zero or negative distance.  Please renter a number\n";
                }
            }
            else {
                cin.clear();	// clear cin errors
                if (cin.peek() != terminationChar) {
                    cin.clear();			//clear cin error if is one
                    cin.ignore(256, '\n');	//clear all entries until new line is found
                    cout << "invalid entry.  Please renter a number\n";
                }
                else {
                    stop = true;
                }
            }
        }
        // print measurements
        if (!enteredMeasurements.empty()) {
            sort(enteredMeasurements.begin(), enteredMeasurements.end(), [](auto &left, auto &right) {
                return left.first < right.first;
            });
            cout << "\n\nValid entered numbers are:\n";
            for (auto itr : enteredMeasurements) {
                cout << itr.first << itr.second << endl;
            }
            cout << "The smallest valid value entered is " << enteredMeasurements.front().first << convetToUnit << endl;
            cout << "The largest valid value entered is " << enteredMeasurements.back().first << convetToUnit << endl;
            cout << "The sum of all valid entered measurements is " << sum << convetToUnit << endl;
        }
    }
    cout << "Bye\n";
    keep_window_open();
    return 0;
}
