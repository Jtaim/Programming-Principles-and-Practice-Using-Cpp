//Written by Jtaim
//Date 2 Dec 2015
//updated 28 Dec 2016
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 9
read digits and compose them into integers. For example, 123 is read as the characters 1, 2, and 3.
Output of 123 is 1 hundred and 2 tens and 3 ones.
The numbers is output as int value.
Handle up to 4 digits.
terminate program with '|'.
*/

#include "section6.h"

void print_number(const std::string& num, const std::vector<std::string>& den);

int main()
{
	constexpr char termination = '|';
	// only have to add or subtract denominations array size and program will adjust.
	const std::vector<std::string> denomination{"ones", "tens", "hundreds", "thousands"};

	try{
		bool LoopAgain{true};
		do{
			std::cout << "Enter a number up to " << denomination.size() << " digits long. Enter " << termination << " to exit\n";
			std::string number;
			size_t itr{};

			char digit{};
			while(std::cin.get(digit)){
				if(digit == '\n'){
					print_number(number, denomination);
					break;
				} else if(!isdigit(digit)){
					if(digit == termination){
						LoopAgain = false;
						break;
					}
					error("found a non number character");
				} else{
					if(itr > denomination.size()){
						error("entered number is too large");
					}
					number.push_back(digit);
					++itr;
				}
			}
		} while(LoopAgain && std::cin);

	}
	catch(std::exception& e){
		std::cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch(...){
		std::cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}

	keep_window_open();
	return 0;
}

void print_number(const std::string& num, const std::vector<std::string>& den)
{
	if(num.empty()){
		std::cout << "no number was entered\n";
	} else{
		std::cout << num << " is ";
		for(size_t i{}, j{num.size() - 1}; i < num.size(); ++i, --j){
			std::cout << num.at(i) << " " << den.at(j)
				<< ((i < num.size() - 1) ? " and " : ".\n");
		}
	}
}
