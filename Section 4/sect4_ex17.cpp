//written by Jtaim
//date 13 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 17. 
A that finds the min, max and mode of a sequence of strings
*/

#include "section4.h" // custom header

int main()
{
	vector<string> input_strings{};  // hold numbers to check mode
	string input_string{};
	cout << "Enter a set of strings so can find the min, max and mode.\n";
	while(true){
		cin >> input_string;
		if (cin.eof()) break;
		else {
			input_strings.push_back(input_string);
		}
	}
	sort(input_strings.begin(),input_strings.end());
    int count = 0;
	int new_count = 0;
	string temp{};
	string mode{};
	for (auto x : input_strings) {
		if (x == temp || temp == "") {
			++new_count;
			temp = x;
			if (new_count >= count) {
				mode = x;
				count = new_count;
			}
		}
		else {
			new_count = 1;
			temp = x;
		}
	}
	if (count > 1) {  // print out the MODE
		cout << "The MODE of entered strings is " << mode << ".\n";
		cout << mode << " was found " << count << " times.\n";
	}
	else {
		cout << "There is no MODE from this set.\n";
	}
	cout << "Maximum string entered was " << input_strings.back() << endl;  // sort function puts them in order for you
	cout << "Minimum string entered was " << input_strings.front() << endl;
	cout << '\n';
	keep_window_open();
	return 0;
}
