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
  std::vector<double> distances;

  std::cout << "Please enter a sequence of numbers (representing distances).\n";

  for (double distance{}; std::cin >> distance; )
  {
    distances.push_back(distance);
  }

  if (distances.empty())
  {
    std::cout << "no distances entered\n";
  }
  else
  {
    double sum{std::accumulate(distances.begin(), distances.end(), 0.0)};
    std::cout << "The total distance: " << sum << std::endl;
    std::sort(distances.begin(), distances.end());
    std::cout << "The smallest distance: " << distances.front() << std::endl;
    std::cout << "The greatest distance: " << distances.back() << std::endl;
    std::cout << "The mean distance: " << sum / distances.size() << std::endl;
  }

  keep_window_open();
  return 0;
}
