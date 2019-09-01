//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 6.
Make a vector holding the ten string values "zero", "one", . . . "nine".
Use that in a program that converts a digit to its corresponding spelled-out value; e.g., the input 7 gives the output seven.
Have the same program, using the same input loop, convert spelled-out numbers into their digit form; e.g., the input seven gives the output 7.
*/

#include "section4.h"

int main()
{
	const std::vector<std::string> spelledNumbers{
		"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
	};

	std::cout << "Enter a number between 0 and 9 either spelled out or as the number.\n";
	int number{};
	if(std::cin >> number){
		if(number >= 0 && number <= 9){
			std::cout << "The number entered is " << spelledNumbers[number] << "\n\n";
		} else{
			std::cout << "numbered entered could not be spelled out.\n";
		}
	}
	// check if number is spelled out
	else{
		std::cin.clear();
		std::string spelledNumber;
		std::cin >> spelledNumber;
		// convert to lower
		std::transform(spelledNumber.begin(), spelledNumber.end(), spelledNumber.begin(), [](char c){
			return static_cast<char>(tolower(c));
		});
		// check if has a spelled out number
		auto spelledIndex = std::find(spelledNumbers.begin(), spelledNumbers.end(), spelledNumber);
		if(spelledIndex != spelledNumbers.end()){
			std::cout << "The number entered is " << (spelledIndex - spelledNumbers.begin()) << "\n\n";
		} else{
			std::cout << "could not find number.\n";
		}
	}

	keep_window_open();
	return 0;
}
