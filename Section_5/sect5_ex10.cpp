//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 10
A program that reads and stores a series of doubles.
Ask user to enter number(N) of doubles want to sum.
Create a vector of the first N doubles.
From that vector calculate the sum of those N doubles.
Also  provide a vector of the delta between delta[1] - delta[0], ..., delta[N] - delta[N-1].
Instruct user to terminate series with '|' when finished entering numbers.
Handle all inputs and provide and error N is larger than input vector
*/

#include "section5.h"

using vType = std::vector<double>;
vType::value_type add(vType::value_type n1, vType::value_type n2);
vType::value_type subtract(vType::value_type n1, vType::value_type n2);

int main()
try
{
    constexpr char termination{ '|' };

    std::cout << "Enter how many numbers that you would like to sum:\n";
    int sumHowMany{};
    if (!(std::cin >> sumHowMany)) {
        error("number expected!");
    }

    // vector to hold the entered numbers
    vType numbers;
    std::cout << "Enter some numbers. (use '" << termination << "' to stop)\n";
    //while loop to get integers to place in a vector, validate and exit on an '|' entry
    while (true) {
        vType::value_type number{};

        // loads entered numbers into a vector container 
        if (std::cin >> number) {
            numbers.push_back(number);
        }
        else {
            std::cin.clear();

            // check if input number was overflowed
            if (number == std::numeric_limits< vType::value_type>::max() ||
                number == std::numeric_limits< vType::value_type>::min()) {
                error("Entered number overflowed number type!");
            }

            // check for proper termination
            char c;
            std::cin >> c;
            if (c == termination) {
                break;
            }
            error("Invalid number or termination!");
        }
    }

    // do we have some numbers ?
    if (numbers.size() >= sumHowMany) {
        vType::iterator stop = numbers.begin() + sumHowMany;
        vType::value_type sum{};

        // sum and check for overflows
        for (auto i = numbers.begin(); i < stop; ++i) {
            sum = add(sum, *i);
        }

        // print the answer
        std::cout << "The sum of the first " << sumHowMany << " numbers.\n";
        for (auto i = numbers.begin(); i < stop; ++i) {
            if (i == (stop - 1)) {
                std::cout << *i << " = " << sum << "\n\n";
            }
            else {
                std::cout << *i << " + ";
            }
        }

        if (numbers.size() > 1) {
            std::cout << "Deltas between the numbers entered are:\n";
            for (auto i = numbers.begin() + 1; i < numbers.end(); ++i) {
                std::cout << *i << " - " << *(i - 1) << " = " << subtract(*i, *(i - 1)) << std::endl;
            }
        }
    }
    else {
        std::cout << "Container was empty.\n";
    }

    keep_window_open();
    return 0;
}
catch (std::exception& e)
{
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...)
{
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}

/*	addition function.
    Inputs:		two numbers
    outputs:	valid resulting number
    Errors:		element overflow
*/
vType::value_type add(vType::value_type n1, vType::value_type n2)
{
    if (((n2 > 0) && (n1 > (std::numeric_limits< vType::value_type>::max() - n2))) ||
        ((n2 < 0) && (n1 < (std::numeric_limits< vType::value_type>::min() - n2)))) {
        error("overflow error");
    }
    return n1 + n2;
}

vType::value_type subtract(vType::value_type n1, vType::value_type n2)
{
    if (((n2 > 0) && (n1 < (std::numeric_limits< vType::value_type>::min() - n2))) ||
        ((n2 < 0) && (n1 > (std::numeric_limits< vType::value_type>::min() - n2)))) {
        error("overflow error");
    }
    return n1 - n2;
}
