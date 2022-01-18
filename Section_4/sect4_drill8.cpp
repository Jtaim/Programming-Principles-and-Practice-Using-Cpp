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
#include <sstream>

int main()
{
  using inputType = double;
  constexpr char terminationChar = '|'; 	//termination character
  constexpr double tolerance = 1.0 / 100;	//close enough for floating point comparison

  constexpr auto convert = std::to_array<std::pair<std::string_view, InputType>>({
    {"m", 100.0},       //covert to cm
    {"cm", 1.00},       //leave as is
    {"in", 2.54},       //convert to cm
    {"ft", 12.0 * 2.54}	//convert to cm
    });

  bool first_loop{true};
  inputType smallest{};
  inputType largest{};

  char c{};
  while (c != terminationChar)
  {
    std::cout << "Enter a number and unit of measure (12in) or enter " << terminationChar << " to exit.\n";

    std::string input;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    inputType enteredNumber;
    ss >> enteredNumber;
    
    // check for valid input
    if (!ss.good())
    {
      ss.clear();
      ss >> c;
      if (c != terminationChar)
      {
        std::cout << "Incomplete entry or invalid termination, please try again.\n";
      }
      continue; //goto next loop cycle
    }

    // get unit of measure
    std::string unitOfMeasure;
    ss >> unitOfMeasure;
    // convert unit of measure to lower case
    std::for_each(unitOfMeasure.begin(), unitOfMeasure.end(), [](auto& c) {c = std::tolower(static_cast<unsigned char>(c)); });

    // check for valid unit of measure and convert
    auto itr = std::find_if(convert.begin(), convert.end(), [&unitOfMeasure](const auto& um) {return um.first == unitOfMeasure; });
    if (itr == convert.end())
    {
      std::cout << unitOfMeasure << " is an unknown unit of measure\n";
      continue; //goto next loop cycle
    }

    // convert measurement to cm
    inputType convertedMeasurement{};
    convertedMeasurement = enteredNumber * itr->second;
    std::cout << "Entered number " << enteredNumber << unitOfMeasure << " was converted to " << convertedMeasurement << "cm";

    //determine if have new smallest or largest number
    if (first_loop)
    {
      first_loop = false;
      smallest = largest = convertedMeasurement;
      std::cout << " and is the smallest and largest so far.";
    }
    if (smallest > convertedMeasurement && std::fabs(smallest - convertedMeasurement) > tolerance)
    {
      smallest = convertedMeasurement;
      std::cout << " and is the smallest so far.";
    }
    else if (largest < convertedMeasurement && std::fabs(largest - convertedMeasurement) > tolerance)
    {
      largest = convertedMeasurement;
      std::cout << " and is the largest so far.";
    }
    std::cout << "\n\n";
  }

  keep_window_open();
  return 0;
}
