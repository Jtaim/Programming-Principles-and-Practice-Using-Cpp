//written by Jtaim
//date 15 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Modify exercise 19 so that when you enter an integer, the program will output all the 
names with that score or score not found.
*/

#include "section4.h" // custom header

int main()
{
	int score{ -1 };
	vector<string> names{ "Moe", "Curly", "Larry", "Shemp" }; //was really 3 stooges
	vector<int> scores{ 1,2,3,2 };
	cout << "Enter a name to find a score.\n";
	// collect valid data
	while (true) {
		bool entry_good = true;
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
			for (int i = 0; i < (names.end() - names.begin()) && names.size() != 0; ++i) {
				if (scores[i] == score) {  // find who has that score
					cout << names[i] << "'s score is " << scores[i] << ".\n";
					entry_good = false;
				}
			}
			if (entry_good) { // no one has that score
				cout << "Score not found.\n";
			}
		}
	}
	keep_window_open();
	return 0;
}