//written by Jtaim
//date 15 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 21.
Modify exercise 19 so that when you enter an integer, the program will output all the 
names with that score or score not found.
*/

#include "section4.h" // custom header

int main()
{
	int score{ -1 };
	vector<string> names{ "Moe", "Curly", "Larry", "Shemp" }; //was there really 4 stooges not 3
	vector<int> scores{ 1,2,5,5 };
	cout << "Enter a name to find a score.\n";
	// collect valid data
	while (names.size() == scores.size()) { // just to insure 2 vectors are the same size
		cin >> score;
		if (cin.eof()) {  // escape if EOF
			break;
		}
		if (cin.fail()) {  // redo if bad input non number for score
			cout << "Entered invalid score.  Please reenter.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else {  // check for name
			auto result = find(begin(scores), end(scores), score);
			if (result != end(scores)) { // found a name match
				while (result != end(scores)) { //find all names with that score
					auto name_to_score = names[(names.size() - (end(scores) - result))];
					cout << name_to_score << "'s score is " << score << ".\n";
					result = find(result+1, end(scores), score); // update to find additional names matching that score
				}
			}
			else { // no scores found
				cout << "Name not found.\n";
			}
		}
	}
	keep_window_open();
	return 0;
}