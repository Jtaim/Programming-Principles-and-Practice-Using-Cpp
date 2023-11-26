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
    using inputType = double;
    constexpr char terminationChar = '|';	//termination character

    char c{};
    while( c != terminationChar )
    {
        std::cout << std::format( "Enter two numbers or enter {} to exit\n", terminationChar );

        inputType val1{}, val2{};
        std::cin >> val1 >> val2;

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

        //print out valid numbers
        std::cout << std::format( "Entered numbers: {} {}\n", val1, val2 );

        //determine and print if numbers are equal
        if( val1 == val2 )
        {
            std::cout << "The entered numbers are equal.\n";
        }
        else
        {
            //determine and print out smallest and biggest
            if( val1 > val2 )
            {
                std::swap( val1, val2 );
            }
            std::cout << std::format( "smaller value is: {}\n", val1 );
            std::cout << std::format( "larger value is: {}\n", val2 );
        }
    }

    keep_window_open();
    return 0;
}
