//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.4.1.3
program that converts yen, euro, pound, yuan, and kroner into dollar
*/

#include "section4.h" //custom header

int main()
{
	using namespace std;
	const vector<pair<const string, const double>> convertRate {
		{"yen", 111.33},
		{"euro", 0.93},
		{"pound", 0.8},
		{"danish krone", 6.8835},
		{"yuan", 6.89}
	};
	double amount{ 1.0 };
	char convertTo{ '?' };
	string currency{ "???" };
	double rate{ -1.0 };
	cout << "Please enter an amount and currency to convert ('$' is to dollars 'o' to other:\n";
	// get currency amount
	if (!(cin >> amount)) {
		simple_error("entered amount unknown");
	}
	// get currency to covert
	cin >> currency;
	// change entered currency to lower case
	for (auto& c : currency) {
		c = static_cast<char>(tolower(c));
	}
	// find rate for entered currency
	auto i = convertRate.begin();
	for (; i < convertRate.end(); ++i) {
		if (i->first == currency) {
			rate = i->second;
			break;
		}
	}
	// check if found valid currency
	if (i == convertRate.end()) {
		simple_error("unknown currency: " + currency);
	}
	// get conversion cammand
	cin >> convertTo;
	
	switch (convertTo)
	{
	case '$':	cout << amount << " " << currency << " == $" << 1 / rate * amount << endl;
				break;
	case 'o':	cout << "$" << amount << " == " << currency << " " << rate * amount << endl;
				break;
	default:	simple_error("unknown conversion command");
	}
	keep_window_open();
}
