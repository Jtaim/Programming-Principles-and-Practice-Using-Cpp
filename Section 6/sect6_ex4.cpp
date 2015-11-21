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

#include "section6.h" // custom header

class Name_value {
public:
	string name{};
	int value{ 0 };
	Name_value() : name{}, value{ 0 } {}   // constructor for init values
	Name_value(string n, int val)
		:name{n}, value(val) { }
};

int main() 
{
	Name_value NS;
	vector<Name_value> vNS;
	cout << "Enter names and scores. \n";
	// collect valid data
	while (true) {
		string n;
		int v;
		cin >> n >> v;
		if (cin.eof() || (n == "NoName" && v == 0)) {  // escape if NoName or EOF
			break;
		}
		if (cin.fail()) {  // redo if bad input non number for score
			cout << "Entered invalid name or score.  Please reenter.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		auto i = vNS.begin();
		for (; i < vNS.end(); ++i) {
			auto a = *i;
			if (a.name == n) break;
		}
		if (i == vNS.end()) {
			NS = { n,v };
			vNS.push_back(NS);
		}
		else {
			cout << "Entered duplicate name.\n";
		}
	}
// print contents to screen
	if (vNS.size() != 0) {
		for (vector<Name_value>::size_type i = 0; i < vNS.size(); ++i) {
			cout << vNS.at(i).name << " " << vNS.at(i).value << endl;
		}
	}
	keep_window_open();
	return 0;
}