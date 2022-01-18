//written by Jtaim
//date 24 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition


/*
Section 3 exercise 9.
a program that converts spelled-out numbers such as “zero” and “two” into digits, such as 0 and 2.
When the user inputs a number, the program should print out the corresponding digit.
Do it for the values 0, 1, 2, 3, and 4 and write out not a number I know if the user enters
something that doesn't correspond, such as stupid computer!.
*/

#include "section3.h"

int main()
{
  using namespace std;

  constexpr string_view lookup[]{"zero", "one", "two", "three", "four"};

  cout << "Enter a spelled out number (example \"two\" for 2)\n";
  for (string spell_num; cin >> spell_num; )
  {
    auto const val = find(cbegin(lookup), cend(lookup), spell_num);
    if (val == cend(lookup))
    {
      cout << spell_num << " is not a number I know!\n";
      break;
    }
    cout << std::format("The entered number {} is the number {}.\n", spell_num, val - cbegin(lookup));
  }

  keep_window_open();
  return 0;
}
