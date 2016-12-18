//written by Jtaim
//date 15 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 21.
Modify exercise 19 so that when you enter an integer, the program will output all the 
names with that score or score not found.
*/

#include "section4.h"
#include <vector>
#include <algorithm>

int main()
{
	using namespace std;

	int score{ -1 };
	vector<string> names{ "Moe", "Curly", "Larry", "Shemp" }; //was there really 4 stooges not 3
	vector<int> scores{ 1,2,5,5 };
	cout << "Enter a name to find a score.\n";
	// collect valid data
	// just to insure 2 vectors are the same size
	while (names.size() == scores.size())
	{
		cin >> score;
		// escape if EOF
		if (cin.eof())
		{
			break;
		}
		// redo if bad input non number for score
		if (cin.fail())
		{
			cout << "Entered invalid score.  Please reenter.\n";
			cin.clear();
			cin.ignore(32768, '\n');
		}
		// check for name
		else
		{
			auto result = find(begin(scores), end(scores), score);
			// found a name match
			if (result != end(scores))
			{
				//find all names with that score
				while (result != end(scores))
				{
					auto name_to_score = names[(names.size() - (end(scores) - result))];
					cout << name_to_score << "'s score is " << score << ".\n";
					// update to find additional names matching that score
					result = find(result + 1, end(scores), score);
				}
			}
			// no scores found
			else
			{
				cout << "Name not found.\n";
			}
		}
	}
	keep_window_open();
	return 0;
}
