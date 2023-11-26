//written by Jtaim
//date 29 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Drill step 11.
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
8. Reject values without units or with “illegal” representations of units,
   such as y, yard, meter, km, and gallons.
9. Keep track of the sum of values entered (as well as the smallest and the largest)
   and the number of values entered. When the loop ends, print the smallest, the largest,
   the number of values, and the sum of values. Note that to keep the sum, you have to
   decide on a unit to use for that sum; use meters.
10.Keep all the values entered (converted into meters) in a vector.
   At the end, write out those values.
11.Before writing out the values from the vector, sort them (that’ll make them come out
   in increasing order).
*/

#include "section4.h"
#include <sstream>

int main()
{
    using inputType = double;
    constexpr char terminationChar = '|';		//termination character
    constexpr double tolerance = 1.0 / 100;	//close enough for floating point comparison

    constexpr auto convert = std::to_array<std::pair<std::string_view, inputType>>( {
      {"m", 1},             //covert to m
      {"cm", .01},          //leave as is
      {"in", .0254},        //convert to m
      {"ft", 12.0 * .0254}  //convert to cm
                                                                                    } );

    bool first_loop{ true };
    inputType smallest{};
    inputType largest{};
    std::vector<inputType> enteredMeasurements;

    std::stringstream ss;
    char c{};
    while( c != terminationChar )
    {
        std::cout << std::format( "Enter a number and unit of measure (12in) or enter {} to exit.\n", terminationChar );
        auto pos = ss.tellg();  // position in the ss buffer
        if( pos == 0 || ss.eof() )
        {
            ss.clear();
            ss.str( "" );
            std::string input;
            std::getline( std::cin, input );
            ss.str( input );
        }
        inputType enteredNumber;
        ss >> enteredNumber;

        // check for valid input
        if( !ss.good() )
        {
            ss.clear();
            ss >> c;
            if( c != terminationChar )
            {
                std::cout << "Incomplete entry or invalid termination, please try again.\n\n";
            }
            continue; //skip rest of loop iteration and start next loop cycle
        }

        // get unit of measure
        std::string unitOfMeasure;
        ss >> unitOfMeasure;
        // convert unit of measure to lower case
        std::for_each( unitOfMeasure.begin(), unitOfMeasure.end(),
                       []( auto& c ) { c = static_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) ); } );

        // check for valid unit of measure and convert
        auto itr = std::find_if( convert.begin(), convert.end(),
                                 [&unitOfMeasure]( const auto& um ) { return um.first == unitOfMeasure; } );
        if( itr == convert.end() )
        {
            std::cout << std::format( "{} is an unknown unit of measure\n\n", unitOfMeasure );
            continue; //skip rest of loop iteration and start next loop cycle
        }

        // convert measurement to m then store in vector
        inputType convertedMeasurement{};
        convertedMeasurement = enteredNumber * itr->second;
        auto output = std::format( "Entered number {}{}  was converted to {}m", enteredNumber, unitOfMeasure, convertedMeasurement );
        enteredMeasurements.push_back( convertedMeasurement );

        //determine if have new smallest or largest number
        if( first_loop )
        {
            first_loop = false;
            smallest = largest = convertedMeasurement;
            output += " and is the smallest and largest so far.";
        }
        if( smallest > convertedMeasurement && std::fabs( smallest - convertedMeasurement ) > tolerance )
        {
            smallest = convertedMeasurement;
            output += " and is the smallest so far.";
        }
        else if( largest < convertedMeasurement && std::fabs( largest - convertedMeasurement ) > tolerance )
        {
            largest = convertedMeasurement;
            output += " and is the largest so far.";
        }
        std::cout << output << "\n\n";
    }

    // print measurements
    std::string stats;
    if( enteredMeasurements.empty() )
    {
        stats = "No measurements to report\n";
    }
    else
    {
        std::sort( enteredMeasurements.begin(), enteredMeasurements.end() );
        stats = std::format( "Number of values entered: {}\n", enteredMeasurements.size() );
        stats += "Values collected:\n";
        for( const auto i : enteredMeasurements )
        {
            stats += std::format( "{}m\n", i );
        }
        stats += std::format( "The smallest valid value entered is {}m\n", smallest );
        stats += std::format( "The largest valid value entered is {}m\n", largest );
        stats += std::format( "The sum of all valid entered measurements is {}m\n",
                              std::accumulate( enteredMeasurements.cbegin(), enteredMeasurements.cend(), 0.0 ) );
    }
    std::cout << stats << "\n\n";

    keep_window_open();
    return 0;
}
