//written by Jtaim
//date 22 Sept 2015
//updated 4 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.2.3
The character 'b' is char('a'+1), 'c' is char('a'+2), etc. Use a loop to write out a table of characters with their corresponding integer values:
a     97
b     98
. . .
z     122
*/

#include "section4.h"	//custom header

int main()
{
	using std::cout;
	for (int index = 97;index <= 122; ++index)	//do to down conversion limit index < 256
	{
		cout << char(index) << '\t' << index << '\t';					//lower case letters
		cout << char(index - 32) << '\t' << index - 32 << std::endl;	//upper case letters
	}
	keep_window_open();
	return 0;
}
