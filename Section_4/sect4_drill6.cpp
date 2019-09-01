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

#include "section4.h"

int main()
{
	constexpr char terminationChar = '|';	//termination character
	const std::string instructions{"Enter two numbers or enter " + std::string{terminationChar} +" to exit."};
	constexpr double tolerance = 1.0 / 100;	//close enough for floating point comparison

	double enteredNumber{};
	std::cout << instructions << '\n';
	char c{};
	while(std::cin.get(c) && c != terminationChar){
		std::cin.putback(c);
		static double min{DBL_MAX};
		static double max{DBL_MIN};
		if(std::cin >> enteredNumber){
			std::cout << "value entered: " << enteredNumber << std::endl;
			if(min > enteredNumber){
				min = enteredNumber;
				std::cout << enteredNumber << " is the smallest so far\n\n";
			}
			if(max < enteredNumber){
				max = enteredNumber;
				std::cout << enteredNumber << " is the largest so far\n\n";
			}
		} else{
			std::cin.clear();
			static std::string getnext;
			std::cin >> getnext;	// get whatever is in cin buffer
			if(getnext.find(terminationChar) != std::string::npos){
				break;
			} else{
				std::cout << "Entry was an invalid number or termination, please try again.\n";
			}
		}
		std::cout << instructions << '\n';
	}

	keep_window_open();
	return 0;
}
