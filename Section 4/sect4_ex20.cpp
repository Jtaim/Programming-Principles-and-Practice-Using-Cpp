//written by Jtaim
//date 15 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Modify exercise 19 so that when you enter a name, the program will output the
corresponding score or name not found.
*/

#include "section4.h" // custom header

int main()
{
	string name{};
	vector<string> names{ "Moe", "Curly", "Larry", "Shemp" }; //was really 3 stooges
	vector<int> scores{ 1,2,3,4 };
	cout << "Enter a name to find a score.\n";
	// collect valid data
	while (true) {
		bool entry_good = true;
		cin >> name;
		if (cin.eof() || name == "NoName") {  // escape if NoName or EOF
			break;
		}
		else {  // check for name
			for (int i = 0; i < (names.end() - names.begin()) && names.size() != 0; ++i) {
				if (names[i] == name) {  // found a name match
					cout << name << "'s score is " << scores[i] << ".\n";
					entry_good = false;
					break;
				}
			}
			if (entry_good) { // no scores by that name
				cout << "Name not found.\n";
			}
		}
	}
	keep_window_open();
	return 0;
}