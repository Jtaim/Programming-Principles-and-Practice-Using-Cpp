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
	const std::string instructions{"Enter two numbers or enter " + std::string{terminationChar} +" to exit."};

	std::cout << instructions << '\n';
	char c{};
	while(std::cin.get(c) && c != terminationChar){
		std::cin.putback(c);
		static double val1{};
		static double val2{};
		if(std::cin >> val1 >> val2){
			if(val1 == val2){
				std::cout << "The entered numbers are equal.\n\n";
			} else{
				if(val1 > val2){
					std::swap(val1, val2);
				}
				std::cout << "smaller value is: " << val1 << std::endl;
				std::cout << "larger value is: " << val2 << std::endl;
			}
		} else{
			std::cin.clear();
			std::cin.get(c);
			if(c == terminationChar){
				break;
			}
			std::cout << "Entry was an invalid number or termination, please try again.\n";
		}
		std::cout << instructions << '\n';
	}

	keep_window_open();
	return 0;
}
