//written by Jtaim
//date 9 Apr 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 6 exercise 4
Rewrite Section 4 exercise 19 with a class Name_value with a string and value object.
Use a vector<Name_value> instead of 2 vectors.
A program where you first enter a set of name-and-value pairs, such as Joe 17 and Barbara 22.
For each pair, add the name to a vector called names and the number to a vector called scores
(in corresponding positions, so that if names[7]=="Joe" then scores[7]==17).
Terminate input with NoName 0.
Check that each name is unique and terminated with an error message if a name is entered twice.
Write out all the (name, score) pairs, one per line.
*/

#include "section6.h"

class Name_value
{
public:
	std::string name;
	int value;
	Name_value()
		: name{ "NoName" }, value{ 0 } {}
	Name_value(std::string n, int val)
		: name{ n }, value(val) {}
};

int main()
{
	using namespace std;
	try
	{
		std::vector<Name_value> vNS;
		cout << "Enter names and scores. Terminate input with NoName 0\n";
		// collect valid data
		bool exit = false;
		while (!exit)
		{
			std::string name;
			int score;
			cin >> name >> score;
			// escape if NoName or EOF
			if (cin.eof() || (name == "NoName" && score == 0)) {
				break;
			}
			// redo if bad input non number for score
			else if (cin.fail()) {
				cout << "Entered invalid name or score.  Please reenter.\n";
				cin.clear();
				cin.ignore(UINT8_MAX, '\n');
			}
			else if (cin.bad()) {
				error("input data error\n");
			}
			else {
				std::transform(name.begin(), name.end(), name.begin(),
					[](unsigned char c) {return narrow_cast<unsigned char>(::tolower(c)); });
				auto result = vNS.begin();
				if (vNS.size() != 0) {
					for (; result < vNS.end(); ++result) {
						if (result->name == name) {
							break;
						}
					}
					if (result == vNS.end()) {
						vNS.push_back({ name, score });
					}
					else {
						error("Entered duplicate name.\n");
					}
				}
				else {
					vNS.push_back({ name, score });
				}
			}
		}
		// print contents to screen
		if (vNS.size() != 0) {
			for (auto i : vNS) {
				cout << i.name << " " << i.value << std::endl;
			}
		}
		else {
			cout << "no names or scores entered\n";
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...)
	{
		std::cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
	cout << "Bye\n";
	keep_window_open();
	return 0;
}
