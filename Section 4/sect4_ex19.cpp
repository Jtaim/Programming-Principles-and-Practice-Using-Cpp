//written by Jtaim
//date 14 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 19.
A program where you first enter a set of name-and-value pairs, such as Joe 17 and Barbara 22.
For each pair, add the name to a vector called names and the number to a vector called scores
(in corresponding positions, so that if names[7]=="Joe" then scores[7]==17).
Terminate input with NoName 0.
Check that each name is unique and terminated with an error message if a name is entered twice.
Write out all the (name, score) pairs, one per line.
*/

#include "section4.h" // custom header

int main()
{
	string name{};
	int score{ 0 };
	vector<string> names;
	vector<int> scores;
	cout << "Enter names and scores. \n";
	// collect valid data
	while (true) {
		cin >> name >> score;
		if (cin.eof() || (name == "NoName" && score == 0)) {  // escape if NoName or EOF
			break;
		}
		if (cin.fail()) {  // redo if bad input non number for score
			cout << "Entered invalid name or score.  Please reenter.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		auto result = find(begin(names), end(names), name);
		if (result != end(names)) {
			cout << "Entered duplicate data.\n";
		}
		else {
			names.push_back(name);
			scores.push_back(score);
		}
	}
// if no duplicates print contents to screen
	if (names.size() != 0) {
		for (int i = 0; i < (names.end() - names.begin()); ++i) {
			cout << names[i] << " " << scores[i] << endl;
		}
	}
	keep_window_open();
	return 0;
}