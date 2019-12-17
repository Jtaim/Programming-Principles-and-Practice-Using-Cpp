//written by Jtaim
//date 23 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3.5 try this exercise
*/

#include "section3.h" //custom header

int main()
{
	std::cout << "A program to check for repeating words. EOF or ctrl-z to exit\n";
	std::cout << "Enter a sentence to check: ";

	std::string previous;
	std::string current;
	unsigned wordCount{};
	while(std::cin >> current){
		++wordCount;
		// make string lower case
		for(auto& c : current){
			c = static_cast<unsigned char>(tolower(c));
		}
		if(previous == current){
			std::cout << "repeated word: " << current << std::endl;
		} else{
			previous = current;
		}
	}
	std::cout << "Total words: " << wordCount << std::endl;

	keep_window_open();
	return 0;
}
