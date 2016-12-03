//written by Jtaim
//date 18 Sept 2015
//updated 1 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition
/*
Section 3.5 try this exercise
*/

#include <iostream>
#include <string>
#include "section3.h" //custom header

//C++ programs start by executing the function main
//exit using EOF ctrl-z
int main()
{
	std::string previous = "";
	std::string current;
	while (std::cin >> current)
	{
		if(previous == current)
		{
			// what if word is repeated but one is capitalized?
			std::cout << "repeated word: " << current << std::endl;
		}
		previous = current;
	}
	return 0;
}