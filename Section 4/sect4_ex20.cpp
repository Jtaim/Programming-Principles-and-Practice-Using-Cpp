//written by Jtaim
//date 15 Oct 2015
//updated 18 Dec 2016
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 20.
Modify exercise 19 so that when you enter a name, the program will output the
corresponding score or name not found.
*/

#include "section4.h"
#include <vector>
#include <algorithm>

int main()
{
	using std::cout;
	using std::cin;

	std::string name{};
	std::vector<std::string> names{ "Moe", "Curly", "Larry", "Shemp" }; //was there really 4 stooges not 3
	std::vector<int> scores{ 1,2,3,4 };
	cout << "Enter a name to find a score.\n";
	// collect valid data
	// just to insure 2 vectors are the same size
	while (names.size() == scores.size())
	{
		cin >> name;
		// escape if NoName or EOF
		if (cin.eof() || name == "NoName")
		{
			break;
		}
		// check for name
		else
		{
			auto result = find(names.begin(), names.end(), name);
			// found a name match
			if (result != names.end())
			{
				auto score_to_match = scores.at((scores.size() - (names.end() - result)));
				cout << name << "'s score is " << score_to_match << ".\n";
			}
			// no name found
			else
			{
				cout << "Name not found.\n";
			}
		}
	}
	keep_window_open();
	return 0;
}
