//written by Jtaim
//date 24 Sept 2015
//updated 10 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 4.
1. Write a program that consists of a while-loop that (each time around the loop)
   reads in two int numbers and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
   numbers and the larger value is: followed by the larger value.
3. Augment the program so that it writes the line the numbers are equal (only) if they are equal.
4. Change the program so that it uses double instead of int.
*/

#include "section4.h"

int main()
{
    constexpr char terminationChar = '|';	//termination character
    constexpr int howManyNumPerItr = 2;		//numbers to get per loop iteration

    double enteredNumber;
    std::vector<decltype(enteredNumber)> enteredNumbers;
    bool stop{ false };
    while (!stop)
    {
        std::cout << "Enter " << howManyNumPerItr << " numbers. Enter " << terminationChar << " to exit.\n";
        for (int itr = 0; itr < howManyNumPerItr; ++itr)
        {
            if (std::cin >> enteredNumber) {
                enteredNumbers.push_back(enteredNumber);
            }
            else {
                std::cin.clear();
                char c;
                std::cin.get(c);
                if (c == terminationChar) {
                    enteredNumbers.clear();
                    stop = true;
                    break;
                }
                else {
                    simple_error("invalid entry:  was not a valid number or termination");
                }
            }
        }
        // print numbers if valid
        if (!stop) {
            std::cout << "Entered numbers: ";
            for (auto i : enteredNumbers) {
                std::cout << i << " ";
            }
            std::cout << std::endl;

            if (enteredNumbers.front() == enteredNumbers.back()) {
                std::cout << "The entered numbers are equal.\n\n";
            }
            else {
                std::sort(enteredNumbers.begin(), enteredNumbers.end());
                std::cout << "smaller value is: " << enteredNumbers.front() << std::endl;
                std::cout << "larger value is: " << enteredNumbers.back() << "\n\n";
            }
        }
        //clear vector for next set of numbers
        enteredNumbers.clear();
    }
    std::cout << "Bye\n";
    keep_window_open();
    return 0;
}
