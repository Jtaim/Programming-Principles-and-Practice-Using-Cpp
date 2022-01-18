//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
 Section 4 exercise 14.
 Modify exercise 13 to take an input value max and then find all prime numbers from 1 to max.
*/

#include "section4.h"

int main()
{
  int max{};
  std::cout << "enter number that want to find all primes up to it." << std::endl;
  if (!(std::cin >> max) || max < 1)
  {
    simple_error("entered invalid integer value or maximum is less than 1\n");
  }

  // build table
  // add 1 to make room for 0 and 1 min size and mark as false
  std::vector<bool> sieve(max + 1, true);
  sieve[0] = sieve[1] = false;

  for (std::size_t i{}; i < sieve.size(); ++i)
  {
    if (sieve[i] == true)
    {
      for (std::size_t j{2}; (j * i) < sieve.size(); ++j)
      {
        sieve[i * j] = false;
      }
    }
  }

  // print out the prime numbers
  constexpr std::size_t minSize = 3;  // min array size to say we have at least 1 prime which is the number 2
  std::cout << "The prime numbers between 1 and " << max << " is " << (sieve.size() < minSize ? "none.\n" : "\n");
  for (std::size_t columnSize{1}, index{minSize - 1}; index != sieve.size(); ++index)
  {
    //10 columns 
    if (sieve[index] == true)
    {
      std::cout << index << (columnSize % 10 != 0 ? '\t' : '\n');
      ++columnSize;
    }
  }
  std::cout << std::endl;

  keep_window_open();
  return 0;
}
