//written by Jtaim
//date 22 Oct 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 5 Try This 5.7 first one
build and test the program from the section.
Does it provide the correct results?
What is the lease amount of input you can give it to get it to fail?
*/

#include "section5.h" //custom header

int main()
{
	vector<double>temps;  // temperatures
	while(true) {
		double temp;
		cin >> temp;
		if(cin.good()) {
			temps.push_back(temp);
		}
		else {  //found non-numeric entry
			cout << "input complete.\n";
			cin.clear();
			cin.ignore(1024, '\n');  // blah, magic number but just to clear cin buffer
			break;
		}
	}
	if(temps.size() != 0) {  // check for empty vector
		auto high_temp = *max_element(temps.begin(), temps.end()); // find high
		auto low_temp = *min_element(temps.begin(), temps.end());  // find low
		auto sum = accumulate(temps.begin(), temps.end(), 0.0); // add up the elements 0.0 to initialize and as double
		cout << "High temperature: " << high_temp << endl;
		cout << "Low temperature: " << low_temp << endl;
		cout << "Average temperature: " << sum / temps.size() << endl;
	}
	else {
		cout << "No temperatures entered.\n";
	}
	keep_window_open();
	return 0;
}