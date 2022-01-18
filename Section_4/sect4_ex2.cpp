//written by Jtaim
//date 30 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 2.
If we define the median of a sequence as "a number so that exactly as many elements come before
it in the sequence as come after it," fix the program in §4.6.3 so that it always prints out a median.
Hint: A median need not be an element of the sequence.
*/

#include "section4.h"

// read some temperatures into a vector
int main()
{
  std::vector<double> temperatures;	// store history of temperatures
  std::cout << "Enter some temperature values and find the medium.\n";

  for (double temperature{}; std::cin >> temperature; )
  {
    temperatures.push_back(temperature);
  }

  // compute mean temperature:
  if (temperatures.empty())
  {
    std::cout << "No temperature data was found\n";
  }
  else
  {
    double sum = std::accumulate(temperatures.begin(), temperatures.end(), 0.0);
    std::cout << "Average number: " << sum / temperatures.size() << std::endl;

    // compute median temperature:
    // If n is odd then Median (M) = value of ((n + 1)/2)th item term.
    // If n is even then Median (M) = value of [((n)/2)th item term + ((n)/2 + 1)th item term ]/2
    sort(temperatures.begin(), temperatures.end());	// sort numbers
    if ((temperatures.size() % 2) != 0)
    {
      std::cout << "Median number: " << temperatures[temperatures.size() / 2] << std::endl;
    }
    else
    {
      // if have even amount, remember vector index starts at zero
      // get 2 middle indexes and divide by 2
      std::cout << "Median number: " << (temperatures[temperatures.size() / 2 - 1] + temperatures[temperatures.size() / 2]) / 2 << std::endl;
    }
  }

  keep_window_open();
  return 0;
}
