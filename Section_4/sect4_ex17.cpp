//written by Jtaim
//date 2 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 17.
finds the min, max and mode of a sequence of strings
*/

#include "section4.h"

int main()
{
	using vType = std::vector<std::string>;
	std::cout << "Enter a set of strings to find the min, max and mode.\n";
	std::cout << "EOF to exit.\n\n";

	vType sequence;  // vector to hold input sequence
	
	for(vType::value_type enteredValue{}; std::cin >> enteredValue; ){
		std::transform(enteredValue.begin(), enteredValue.end(), enteredValue.begin(),
			[](char c){return static_cast<unsigned char>(tolower(c)); });
		sequence.push_back(enteredValue);
	}

	if(!sequence.empty()){
		std::sort(sequence.begin(), sequence.end());
		vType::value_type mode{};
		vType::difference_type count{};

		// search sorted vector for most duplicates
		for(auto i{sequence.cbegin()}, next{sequence.cbegin()}; i != sequence.end(); i = next){
			next = std::find_if_not(i, sequence.cend(), [i](vType::value_type comp){return *i == comp; });
			auto temp_count{next - i};
			if(temp_count >= count){
				count = temp_count;
				mode = *i;
			}
		}

		// print out the MODE
		if(count > 1){
			std::cout << "The MODE of entered sequence is " << mode << ".\n";
			std::cout << mode << " was found " << count << " times.\n";
		} else{
			std::cout << "There is no MODE from this set.\n";
		}

		std::cout << "Maximum string entered was " << sequence.back() << "\n";
		std::cout << "Minimum string entered was " << sequence.front() << "\n";
	} else{
		std::cout << "nothing entered\n";
	}

	keep_window_open();
	return 0;
}
