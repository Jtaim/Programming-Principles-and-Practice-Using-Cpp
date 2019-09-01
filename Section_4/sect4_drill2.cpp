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

#include "section4.h"

int main()
{
	constexpr char terminationChar = '|';	//termination character
	const std::string instructions{"Enter two numbers or enter " + std::string{terminationChar} +" to exit."};

	std::cout << instructions << '\n';
	char c{};
	while(std::cin.get(c) && c != terminationChar){
		std::cin.putback(c);
		static int val1{};
		static int val2{};
		if(std::cin >> val1 >> val2){
			if(val1 > val2){
				std::swap(val1, val2);
			}
			std::cout << "smaller value is: " << val1 << std::endl;
			std::cout << "larger value is: " << val2 << std::endl;
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
