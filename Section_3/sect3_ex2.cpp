//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 3 exercise 2.
converts from miles to kilometers (1.609 kilometers to the mile)
*/

#include "section3.h"

int main()
{
  using namespace std;

  cout << "Enter the number of miles you want to convert to kilometers: ";
  double miles{};
  if (cin >> miles)
  {
    cout << std::format("{} {} equals {} {}\n",
      miles, miles == 1 ? "mile" : "miles",
      miles * 1.609, miles * 1.609 == 1 ? "kilometer" : "kilometers");
  }
  else
  {
    simple_error("Invalid entry");
  }

  keep_window_open();
  return 0;
}
