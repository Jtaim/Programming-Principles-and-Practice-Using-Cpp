//written by Jtaim
//date 28 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 8.
1. Write a program that consists of a while-loop that (each time around the loop)
   reads in two int numbers and then prints them. Exit the program when a terminating '|' is entered.
2. Change the program to write out the smaller value is: followed by the smaller of the
   numbers and the larger value is: followed by the larger value.
3. Augment the program so that it writes the line the numbers are equal (only) if
   they are equal.
4. Change the program so that it uses double instead of int.
5. Change the program so that it writes out the numbers are almost equal after writing
   out which is the larger and the smaller if the two numbers differ by less than 1.0 / 100.
6. Now change the body of the loop so that it reads just one double each time around.
   Define two variables to keep track of which is the smallest and which is the largest
   value you have seen so far. Each time through the loop write out the value entered.
   If it’s the smallest so far, write the smallest so far after the number.
   If it is the largest so far, write the largest so far after the number.
7. Add a unit to each double entered; that is, enter values such as 10cm, 2.5in, 5ft,
   or 3.33m. Accept the four units: cm, m, in, ft. Assume conversion factors
   1m == 100cm, 1in == 2.54cm, 1ft == 12in. Read the unit indicator into a string.
   You may consider 12 m (with a space between the number and the unit) equivalent to 12m (without a space).
8. Reject values without units or with "illegal" representations of units,
   such as y, yard, meter, km, and gallons.
*/

#include "section4.h"
#include <unordered_map>

int main()
{
	constexpr char terminationChar = '|';	//termination character
	const std::string instructions{"Enter a number with unit of measurement or enter " + std::string{terminationChar} +" to exit."};
	constexpr double tolerance = 1.0 / 100;	//close enough for floating point comparison

	const std::unordered_map<std::string, double> convert{
		{"m", 100.0},	//covert to cm
		{"cm", 1.00},	//leave as is
		{"in", 2.54},	//convert to cm
		{"ft", 12.0 * 2.54}	//convert to cm
	};

	std::cout << instructions << '\n';
	char c{};
	while(std::cin.get(c) && c != terminationChar){
		std::cin.putback(c);
		static double min{DBL_MAX};
		static double max{DBL_MIN};

		// get number
		static double enteredMeasurement{};
		std::cin >> enteredMeasurement;
		if(!std::cin){
			std::cin.clear();
			// if no number entered then assume 1 as the measurement
			enteredMeasurement = 1.0;
		}

		// get unit of measure
		static std::string unitOfMeasure;
		std::cin >> unitOfMeasure;
		// check for valid unit of measure and convert
		auto itr{convert.find(unitOfMeasure)};
		// convert measurement to cm then store in vector
		if(itr != convert.end()){
			static double convertedMeasurement{};
			convertedMeasurement = enteredMeasurement * itr->second;
			std::cout << enteredMeasurement << unitOfMeasure << " converted to " << convertedMeasurement << "cm\n";
			if(min > convertedMeasurement){
				min = convertedMeasurement;
				std::cout << convertedMeasurement << "cm is the smallest so far\n\n";
			}
			if(max < convertedMeasurement){
				max = convertedMeasurement;
				std::cout << convertedMeasurement << "cm is the largest so far\n\n";
			}
		} else if(unitOfMeasure.find(terminationChar) != std::string::npos){
			break;
		} else{
			std::cout << "Entry was an invalid unit of measure or termination, please try again.\n";
		}
		std::cout << instructions << '\n';
	}
	std::cout << "termination '" << terminationChar << "' found\n";

	keep_window_open();
	return 0;
}
