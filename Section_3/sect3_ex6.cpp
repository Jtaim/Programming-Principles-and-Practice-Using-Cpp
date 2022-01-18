// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 6.
A program that prompts the user to enter three integer values,
and then outputs the values in numerical sequence separated by commas.
So, if the user enters the values 10 4 6, the output should be 4, 6, 10.
If two values are the same, they should just be ordered together.
So, the input 4 5 4 should give 4, 4, 5.
*/

#include "section3.h"

int main()
{
  using namespace std;

  cout << "A program that prompts the user to enter three integer values,\n"
    << "and then outputs the values in numerical sequence separated by commas.\n\n"
    << "Enter three integer values:\n";

  int min{std::numeric_limits<int>::max()};
  int mid{std::numeric_limits<int>::max()};
  int max{std::numeric_limits<int>::max()};

  decltype(min) val{};
  for (std::size_t i{}; i < 3 && cin >> val; ++i)
  {
    decltype(min) temp{};
    if (val < min)
    {
      temp = min;
      min = val;
      val = mid;
      mid = temp;
      max = val;
    }
    else if (val < mid)
    {
      temp = mid;
      mid = val;
      max = temp;
    }
    else
    {
      max = val;
    }
  }

  if (!(cin))
  {
    simple_error("Invalid entry");
  }

  cout << std::format("{} , {}, {}", min, mid, max);

  keep_window_open();
  return 0;
}
