//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
 Section 4 exercise 15.
 A program that takes an input value n and then finds the first n primes
*/

#include "section4.h"

int main()
{
  // container to store the prime numbers
  std::vector<int> primes{};

  std::size_t howManyToFind{};
  std::cout << "enter number of primes you want to find." << std::endl;
  if (!(std::cin >> howManyToFind))
  {
    simple_error("entered invalid integer value\n");
  }

  // loop to found n primes and start with 2.
  for (std::size_t i{2}; primes.size() < howManyToFind; ++i)
  {
    auto check = std::find_if(primes.cbegin(), primes.cend(), [i](auto p) { return i % p == 0; });
    if (check == primes.cend())
    {
      primes.push_back(i);
    }
  }

  // print out the prime numbers
  std::cout << "The number of primes found is " << primes.size() << ".\n";
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
