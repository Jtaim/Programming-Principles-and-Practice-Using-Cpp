//written by Jtaim
//date 11 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 15. 
A program that finds the mode of a set of positive integers
The "mode" is the value that occurs most often. 
If no number is repeated, then there is no mode for the list.
Refer to drill 3
*/

#include "section4.h" // custom header

int main()
{
	vector<int> pos_ints{ };  // hold numbers to check mode
	int n = -1;
	cout << "Enter a set of positive integers so can find the MODE.\n";
	while(true){
		cin >> n;
		if (cin.fail()  || n<0) {
			if(cin.eof()) break;
			cout << "entered an invalid number. Re-enter the number.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else {
			pos_ints.push_back(n);
		}
	}
	sort(pos_ints.begin(),pos_ints.end());
	int count = 0;
	int new_count = 0;
	int temp = -1;
	int mode = 0;
	for (auto x : pos_ints) {
		if (x == temp || temp == -1) {
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
		cout << "The MODE of entered integers is " << mode << ".\n";
		cout << mode << " was found " << count << " times.\n";
	}
	else {
		cout << "There is no MODE from this set.\n";
	}
	cout << "Numbers entered and sorted were:\n";
	int j = 1;
	for (auto x : pos_ints) { // print out the prime numbers
		if (j % 10) {  //10 per row
			cout << x << '\t';
		}
		else {
			cout << x << '\n';
		}
		j++;
	}
	cout << '\n';
	keep_window_open();
	return 0;
}