//written by Jtaim
//date 15 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 20.
Modify exercise 19 so that when you enter a name, the program will output the
corresponding score or name not found.
*/

#include "section4.h" // custom header

int main()
{
	string name{};
	vector<string> names{ "Moe", "Curly", "Larry", "Shemp" }; //was there really 4 stooges not 3
	vector<int> scores{ 1,2,3,4 };
	cout << "Enter a name to find a score.\n";
	// collect valid data
	while (names.size() == scores.size()) { // just to insure 2 vectors are the same size
		cin >> name;
		if (cin.eof() || name == "NoName") {  // escape if NoName or EOF
			break;
		}
		else {  // check for name
			auto result = find(begin(names), end(names), name);
			if(result != end(names)) { // found a name match
				auto score_to_match = scores[(scores.size() - (end(names) - result))];
				cout << name << "'s score is " << score_to_match << ".\n";
			}
			else { // no name found
				cout << "Name not found.\n";
			}
		}
	}
	keep_window_open();
	return 0;
}