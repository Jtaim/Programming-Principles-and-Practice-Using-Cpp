//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 3.
Read a sequence of double values into a vector.
Think of each value as the distance between two cities along a given route.
Compute and print the total distance (the sum of all distances).
Find and print the smallest and greatest distance between two neighboring cities.
Find and print the mean distance between two neighboring cities.
*/

#include "section4.h"

int main()
{
    constexpr auto termination{ '|' };
    std::vector<double> distances;

    std::cout << "Please enter a sequence of numbers (representing distances).\n";
    std::cout << "Use '" << termination << "' after last distance entered:\n";

    while (true) {
        for (double distance{ 0.0 }; std::cin >> distance; ) {
            distances.push_back(distance);
        }
        // EOF is captured when using txt file
        if (std::cin.eof() || std::cin.bad()) {
            std::cin.clear();
            break;
        }
        std::cin.clear();
        char c;
        std::cin.get(c);
        if (c == termination) {
            break;
        }
        // loop back to enter valid input
        std::cout << "Unknown input: '" << c << "': Try again\n";
    }

    if (!distances.empty()) {
        double sum = std::accumulate(distances.begin(), distances.end(), 0.0);
        std::cout << "The total distance: " << sum << std::endl;
        std::sort(distances.begin(), distances.end());
        std::cout << "The smallest distance: " << distances.front() << std::endl;
        std::cout << "The greatest distance: " << distances.back() << std::endl;
        std::cout << "The mean distance: " << sum / distances.size() << std::endl;
    }
    else {
        std::cout << "no distances entered\n";
    }

    keep_window_open();
    return 0;
}
