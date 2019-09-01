//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 8
A program that reads and stores a series of integers.
Ask user to enter number(N) of integers want to sum.
Create a vector of the first N integers.
From that vector calculate the sum of those N integers.
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.h"

int main()
try{
	constexpr char termination{'|'};
	using vType = std::vector<int>;

	std::cout << "Enter how many numbers that you would like to sum:\n";

	int sumHowMany{};
	if(!(std::cin >> sumHowMany)){
		error("number expected!");
	}

	vType numbers;
	std::cout << "Enter some numbers (press '" << termination << "' to stop)\n";
	//while loop to get integers to place in a vector, validate and exit on an '|' entry
	while(true){
		vType::value_type number{};
		// loads entered numbers into a vector container 
		if(std::cin >> number){
			numbers.push_back(number);
		} else{
			std::cin.clear();
			char c{};
			std::cin >> c;
			if(c == termination){
				break;
			}
			error("Invalid number or termination!");
		}
	}

	if(numbers.size() >= sumHowMany){
		vType::iterator stop{numbers.begin() + sumHowMany};
		// sum numbers to specified value. initialize with vector value type set to 0.
		vType::value_type sum{std::accumulate(numbers.begin(), stop, vType::value_type{})};
		std::cout << "The sum of the first " << sumHowMany << " numbers ";
		for(auto i = numbers.begin(); i != stop; ++i){
			if(i == (stop - 1)){
				std::cout << *i << " = " << sum << std::endl;
			} else{
				std::cout << *i << " + ";
			}
		}
	} else{
		error("not enough numbers entered to sum!");
	}

	keep_window_open();
	return 0;
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
