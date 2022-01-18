//written by Jtaim
//date 2 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Add comments here
*/

#include "section5.h"

int main()
try
{
  /*<<your code here>>*/
  keep_window_open();
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
