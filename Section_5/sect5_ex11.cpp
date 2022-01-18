//written by Jtaim
//date 7 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 11
A program that writes out the Fibonacci series up to largest to fit in an int type
*/

#include "section5.h"

using vType = std::vector<int>;
vType::value_type add(vType::value_type n1, vType::value_type n2);

int main()
try
{
  vType fibonacci{1,1};
  for (vType::difference_type i{}; /*intentional no conditional*/; ++i)
  {
    std::cout << fibonacci[i] << std::endl;
    fibonacci.push_back(add(fibonacci[i], fibonacci[i + 1]));
  }

  keep_window_open();	// yes I know will never get to this point
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
    ((n2 < 0) && (n1 < (std::numeric_limits< vType::value_type>::min() - n2))))
  {
    error("overflow error");
  }
  return n1 + n2;
}
