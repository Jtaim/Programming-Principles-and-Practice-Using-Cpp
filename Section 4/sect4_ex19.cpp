//written by Jtaim
//date 14 Oct 2015
//update 18 Dec 2016
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

#include "section4.h"
#include <vector>
#include <algorithm>

int main()
{
	using std::cout;
	using std::cin;

	std::string name;
	int score{ 0 };
	std::vector<std::string> names;
	std::vector<int> scores;
	cout << "Enter names and scores. \n";
	// collect valid data
	while (true)
	{
		cin >> name >> score;
		// escape if NoName or EOF
		if (cin.eof() || (name == "NoName" && score == 0))
		{
			break;
		}
		// redo if bad input non number for score
		if (cin.fail())
		{
			cout << "Entered invalid name or score.  Please reenter.\n";
			cin.clear();
			cin.ignore(32768, '\n');
		}
		auto result = find(names.begin(), names.end(), name);
		if (result != names.end())
		{
			cout << "Entered duplicate data.\n";
		}
		else
		{
			names.push_back(name);
			scores.push_back(score);
		}
	}
	// if no duplicates print contents to screen
	if (names.size() != 0)
	{
		for (int i = 0; i < (names.end() - names.begin()); ++i)
		{
			cout << names.at(i) << " " << scores.at(i) << std::endl;
		}
	}
	keep_window_open();
	return 0;
}
