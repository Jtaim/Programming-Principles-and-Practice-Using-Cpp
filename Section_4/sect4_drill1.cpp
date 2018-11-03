//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 1.
Write a program that consists of a while-loop that (each time around the loop) reads in
two INTs and then prints them. Exit the program when a terminating '|' is entered.
*/

#include "section4.h"	//custom header

int main()
{
    using namespace std;
    const char terminationChar = '|';	//termination character
    const int howMany = 2;				//numbers to get per loop iteration

    int enteredNumber;
    vector<decltype(enteredNumber)> enteredNumbers;
    bool stop = false;
    while (!stop)
    {
        cout << "Enter two numbers. Enter " << terminationChar << " to exit.\n";
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
        if (!stop) {
            cout << "Entered numbers: ";
            for (auto i : enteredNumbers) {
                cout << i << " ";
            }
            cout << endl;
        }
        //clear vector for next set of numbers
        enteredNumbers.clear();
    }
    cout << "Bye\n";
    keep_window_open();
    return 0;
}
