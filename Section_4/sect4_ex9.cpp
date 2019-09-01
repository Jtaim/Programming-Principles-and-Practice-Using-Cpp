//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 9.
 Try to calculate the number of rice grains that the inventor asked for in exercise 8 above.
 You'll find that the number is so large that it won't fit in an int or a double.
 Observe what happens when the number gets too large to represent exactly as an int and as a double.
 What is the largest number of squares for which you can calculate the exact number of grains (using an int)?
 What is the largest number of squares for which you can calculate the approximate number of grains (using a double)?
*/

#include "section4.h"

int main()
{
	std::cout << "The maximum number represented int on this PC is " << std::numeric_limits<int>::max() << std::endl;
	std::cout << "The maximum number represented unsigned on this PC is " << std::numeric_limits<unsigned>::max() << std::endl;
	std::cout << "The maximum number represented long on this PC is " << std::numeric_limits<long>::max() << std::endl;
	std::cout << "The maximum number represented unsigned long on this PC is " << std::numeric_limits<unsigned long>::max() << std::endl;
	std::cout << "The maximum number represented long long on this PC is " << std::numeric_limits<long long>::max() << std::endl;
	std::cout << "The maximum number represented unsigned long long on this PC is " << std::numeric_limits<unsigned long long>::max() << std::endl;
	std::cout << "The maximum number represented double on this PC is " << std::numeric_limits<double>::max() << std::endl;
	std::cout << "The maximum number represented long double on this PC is " << std::numeric_limits<long double>::max() << std::endl;

	constexpr int maxSquares = 64;

	unsigned long long current_square_grains{1};
	decltype(current_square_grains) previous_square_grains{0};
	std::cout << "\nsize of square = " << sizeof(current_square_grains) << " bytes\n";
	std::cout << "max limit of square = " << std::numeric_limits<decltype(current_square_grains)>::max() << "\n\n";

	decltype(current_square_grains) sum{0};
	for(int square = 1; square <= maxSquares; ++square){
		if(square == 1){
			current_square_grains = 1;
		} else{
			current_square_grains = previous_square_grains * 2;
		}
		//std::cout << "square " << square << " = " << current_square_grains << " grains\n";
		previous_square_grains = current_square_grains;


		// add them up
		sum += current_square_grains;
		//std::cout << "Sum of the squares to this point is " << sum << " grains.\n\n";

		if(current_square_grains <= 1000 && sum >= 1000){
			std::cout << square << " provides approximately 1000 grains.\n\n";
		} else if(current_square_grains <= 1000000 && sum >= 1000000){
			std::cout << square << " provides approximately 1,000,000 grains.\n\n";
		} else if(current_square_grains <= 1000000000 && sum >= 1000000000){
			std::cout << square << " provides approximately 1,000,000,000 grains.\n\n";
		} else if(current_square_grains <= 1000000000000 && sum >= 1000000000000){
			std::cout << square << " provides approximately 1,000,000,000,000 grains.\n\n";
		} else if(current_square_grains <= 1000000000000000 && sum >= 1000000000000000){
			std::cout << square << " provides approximately 1,000,000,000,000,000 grains.\n\n";
		} else if(current_square_grains <= 1000000000000000000 && sum >= 1000000000000000000){
			std::cout << square << " provides approximately 1,000,000,000,000,000,000 grains.\n\n";
		}
	}

	keep_window_open();
	return 0;
}
