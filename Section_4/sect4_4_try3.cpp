//written by Jtaim
//date 26 Mar 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.2.1
The character 'b' is char('a'+1), 'c' is char('a'+2), etc.
Use a loop to write out a table of characters with their corresponding integer values:
a     97
b     98
. . .
z     122
*/

#include "section4.h"

int main()
{
  char character{'a'};	// 97 = 'a' lower case letters 122 = 'z'
  while (character <= 'z')
  {
    std::cout << character << "\t" << static_cast<int>(character) << std::endl;
    ++character;
  }

  keep_window_open();
  return 0;
}
