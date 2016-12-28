//written by Jtaim
//date 19 Nov 2015
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
		: name{}, value{ 0 } {}
	Name_value(std::string n, int val)
		: name{ n }, value(val) { }
};

int main()
{
	using std::cout;
	using std::cin;

	Name_value NS;
	std::vector<Name_value> vNS;
	cout << "Enter names and scores. Terminate input with NoName 0\n";
	// collect valid data
	bool exit = false;
	while (!exit)
	{
		std::string n;
		int v;
		cin >> n >> v;
		// escape if NoName or EOF
		if (cin.eof() || (n == "NoName" && v == 0))
		{
			cin.clear();
			exit = true;
		}
		// redo if bad input non number for score
		else if (!cin.good())
		{
			cout << "Entered invalid name or score.  Please reenter.\n";
			cin.clear();
			cin.ignore(UINT_MAX, '\n');
		}
		else
		{
			std::transform(n.begin(), n.end(), n.begin(), ::tolower);
			auto itr = vNS.begin();
			for (; itr < vNS.end(); ++itr)
			{
				if (itr->name == n)
				{
					break;
				}
			}
			if (itr == vNS.end())
			{
				NS = { n,v };
				vNS.push_back(NS);
			}
			else
			{
				cout << "Entered duplicate name.\n";
			}
		}
	}
	// print contents to screen
	if (vNS.size() != 0)
	{
		for (auto i : vNS)
		{
			cout << i.name << " " << i.value << std::endl;
		}
	}
	else
	{
		cout << "no names or scores entered\n";
	}
	cout << "Bye\n";
	keep_window_open();
	return 0;
}
