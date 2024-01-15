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

#include "section4.hpp"

int main()
{
    using inputType = double;
    constexpr char terminationChar = '|';	//termination character
    constexpr double tolerance = 1.0 / 100;	//close enough for floating point comparison

    bool first_loop{ true };
    inputType smallest{};
    inputType largest{};

    char c{};
    while( c != terminationChar )
    {
        std::cout << std::format( "Enter a number or enter {} to exit.\n", terminationChar );

        inputType enteredNumber;
        std::cin >> enteredNumber;

        //check for valid input
        if( !std::cin.good() )
        {
            std::cin.clear();
            std::cin.get( c );
            if( c != terminationChar )
            {
                std::cout << "Invalid number or termination, please try again.\n";
            }
            continue; //goto next loop cycle
        }

        //print out valid number
        std::cout << std::format( "Entered number: {}", enteredNumber );

        if( first_loop )
        {
            first_loop = false;
            smallest = largest = enteredNumber;
            std::cout << " is the smallest and largest so far.";
        }
        //determine if have new smallest or largest number
        if( smallest > enteredNumber && std::fabs( smallest - enteredNumber ) > tolerance )
        {
            smallest = enteredNumber;
            std::cout << " is the smallest so far.";
        }
        else if( largest < enteredNumber && std::fabs( largest - enteredNumber ) > tolerance )
        {
            largest = enteredNumber;
            std::cout << " is the largest so far.";
        }
        std::cout << std::endl;
    }

    keep_window_open();
    return 0;
}
