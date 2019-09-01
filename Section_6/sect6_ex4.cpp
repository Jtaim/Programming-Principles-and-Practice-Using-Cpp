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
	double score{};
	Name_value(std::string n = "", double val = 0)
		: name{n}, score(val) {}
};

bool operator==(const Name_value& nv1, const Name_value& nv2)
{
	return (nv1.name == nv2.name && nv1.score == nv2.score);
}

bool operator!=(const Name_value& nv1, const Name_value& nv2)
{
	return !(nv1 == nv2);
}

const Name_value termination{"noname", 0};

int main()
{
	using namespace std;

	try{
		vector<Name_value> ranks;
		cout << "Enter names and scores. Terminate input with NoName 0\n";
		// collect valid data
		while(true){
			Name_value nv;
			cin >> nv.name >> nv.score;
			// escape if NoName or EOF
			if(cin.eof()){
				break;
			}
			// redo if bad input non number for score
			else if(cin.fail()){
				cout << "Entered invalid name or score.  Please reenter.\n";
				cin.clear();
				cin.sync_with_stdio(false);
				cin.ignore(cin.rdbuf()->in_avail());
				continue;
			} else if(cin.bad()){
				error("input data error\n");
			}

			std::transform(nv.name.begin(), nv.name.end(), nv.name.begin(),
				[](unsigned char c){return narrow_cast<unsigned char>(::tolower(c)); });

			// check if duplicated
			if(ranks.cend() != std::find_if(ranks.cbegin(), ranks.cend(),
				[&nv](Name_value ns){return ns.name == nv.name; })){
				error("found a duplicated name");
			}

			if(nv == termination){
				break;
			}

				ranks.push_back({nv.name, nv.score});
		}

		// print contents to screen
		if(!ranks.empty()){
			for(const auto i : ranks){
				std::cout << "name: " << i.name << "\tscore: " << i.score << "\n";
			}
		} else{
			cout << "no names or scores entered\n";
		}
	}
	catch(std::exception& e){
		std::cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch(...){
		std::cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}

	keep_window_open();
	return 0;
}
