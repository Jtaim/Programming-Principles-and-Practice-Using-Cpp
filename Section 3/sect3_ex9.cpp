//written by Jtaim
//date 19 Sept 2015
//updated 2 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3 exercise 9.
a program that converts spelled-out numbers such as “zero” and “two” into digits, such as 0 and 2. 
When the user inputs a number, the program should print out the corresponding digit. 
Do it for the values 0, 1, 2, 3, and 4 and write out not a number I know if the user enters 
something that does’t correspond, such as stupid computer!.
*/

#include "section3.h" //custom header

int main()
{
	std::cout << "Enter an spelled out number (example \"two\" for 2) type \"quit\" to exit:\n";
	std::string spell_num;
	while (std::cin >> spell_num)
	{
		int val = -1;
		if (spell_num == "zero")
			val = 0;
		else if (spell_num == "one")
			val = 1;
		else if (spell_num == "two")
			val = 2;
		else if (spell_num == "three")
			val = 3;
		else if (spell_num == "four")
			val = 4;
		else if (spell_num == "quit")
			exit(0);
		else
			std::cout << "spelled out number does not compute try again\n";
		if (val >= 0 && val <= 4)
			std::cout << "The entered number " << spell_num << " is the number " << val << std::endl;
	}
	return 0;
}
