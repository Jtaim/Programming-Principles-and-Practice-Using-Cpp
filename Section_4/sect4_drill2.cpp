//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 2.
1. Write a program that consists of a while-loop that (each time around the loop)
reads in two INTs and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
numbers and the larger value is: followed by the larger value.
*/

#include "section4.hpp"

int main()
{
    constexpr char terminationChar = '|';	//termination character
    char c{};
    while( c != terminationChar )
    {
        std::cout << std::format( "Enter two numbers or enter {} to exit\n", terminationChar );

        int val1{}, val2{};
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

        //determine and print out smallest and biggest
        if( val1 > val2 )
        {
            std::swap( val1, val2 );
        }
        std::cout << std::format( "smaller value is: {}\n", val1 );
        std::cout << std::format( "larger value is: {}\n", val2 );
    }

    keep_window_open();
    return 0;
}
