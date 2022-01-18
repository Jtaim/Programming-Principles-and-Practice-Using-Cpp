//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
 Section 4 exercise 12.
 Modify the program described in the previous exercise 11 to take an input value max
 and then find all prime numbers from 1 to max.
*/

#include "section4.h"

int main()
{
  // container to store the prime numbers
  std::vector<int> primes{};

  int max{};
  std::cout << "enter number that want to find all primes up to it." << std::endl;
  if (!(std::cin >> max) || max < 1)
  {
    simple_error("entered invalid integer value or maximum is less than 1\n");
  }

  // start with 2
  for (int i{2}; i <= max; ++i)
  {
    auto check = std::find_if(primes.cbegin(), primes.cend(), [i](auto p) { return i % p == 0; });
    if (check == primes.cend())
    {
      primes.push_back(i);
    }
  }

  // print out the prime numbers
  std::cout << "The amount of prime numbers between 1 and " << max << " is " << (primes.empty() ? 0 : primes.size()) << ".\n";
  for (int j{1}; auto x : primes)
  {
    //10 per row
    std::cout << x << (j % 10 != 0 ? '\t' : '\n');
    ++j;
  }

  std::cout << std::endl;
  keep_window_open();
  return 0;
}
