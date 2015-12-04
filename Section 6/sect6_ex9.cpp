//Written by Jtaim
//Date 2 Dec 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 9

*/

#include "section6.h"

void char_num(const string& ch, vector<int>& dig)
{
	for (auto digit : ch) {
		if (!(isdigit(digit))) { // invalid digit will empty vector
			dig.clear();
			break;
		}
		dig.push_back(digit-'0'); // convert to integer
	}
}

string need_and(unsigned size, unsigned were)
{
	return (size > were ? " and " : " ");
}

int main()
try
{
	cout << "Enter a number up to 4 digits long.\n";
	string number{};
	while (cin >> number) {
		if (number.size() > 5) {
			cin.clear();
			cin.ignore(UINT8_MAX, '\n');
			cout << "Entry is incorrect, try again.\n";
		}
		else {
			vector<int> valid_digits{};
			char_num(number, valid_digits); // convert string to individual integers plus check for valid digits
			if (valid_digits.empty()) {
				cout << "Entry is incorrect, try again.\n";
			}
			else {
				unsigned size = valid_digits.size();
				cout << number << " is";
				for (auto itr = size; itr != 0; --itr) { // cycle through the string. Also easier to add additional case for higher numbers
					switch (itr) {
					case 1:
						cout << need_and(size, itr) << valid_digits.at(size - itr) << " ones.";
						break;
					case 2:
						cout << need_and(size, itr) << valid_digits.at(size - itr) << " tens";
						break;
					case 3:
						cout << need_and(size, itr) << valid_digits.at(size - itr) << " hundreds";
						break;
					case 4:
						cout << need_and(size, itr) << valid_digits.at(size - itr) << " thousands";
						break;
					default:
						error("How did I get here?\n");
					}
				}
				cout << '\n';
				break;
			}
		}
	}
	keep_window_open();
	return 0;
}
catch (exception& e) 
{
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) 
{
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}