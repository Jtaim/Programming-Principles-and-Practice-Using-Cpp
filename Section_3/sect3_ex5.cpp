// written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3 exercise 5
repeat exercise 4 using double values
Write your program to determine the smaller, larger, sum, difference,
product, and ratio of these values and report them to the user.
*/

#include "section3.h"

int main()
{
  using namespace std;

  cout << "Enter two double values:\n";
  double val1{};
  double val2{};

  if (!(cin >> val1 >> val2))
  {
    simple_error("Invalid entry!");
  }

  if (val1 < val2)
  {
    cout << std::format("{} is smaller than {}\n", val1, val2);
  }
  else if (val1 > val2)
  {
    cout << std::format("{1} is smaller than {0}\n", val1, val2);
  }
  else if (val1 == val2)
  {
    cout << std::format("{} is equal to {}\n", val1, val2);
  }
  else
  {
    simple_error("Not sure how I got here?");
  }

  cout << std::format("{} + {} = {}\n", val1, val2, val1 + val2);
  cout << std::format("{} - {} = {}\n", val1, val2, val1 - val2);
  cout << std::format("{} * {} = {}\n", val1, val2, val1 * val2);
  if (val2 == 0)
  {
    simple_error("I don't divide by zero");
  }
  else
  {
    cout << std::format("{} / {} = {}\n", val1, val2, val1 / val2);
  }

  keep_window_open();
  return 0;
}
