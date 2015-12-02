//Written by Jtaim
//Date 1 Dec 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 8
Rewrite Section 5 exercise 12 Bulls and Cows game to use 4 letters not 4 numbers.
*/

#include "section6.h"
bool get_guesses(vector<char>&, const unsigned);
int get_bulls(const vector<char>&, vector<char>&);
int get_cows(const vector<char>&, vector<char>&);

int main()
try
{
	vector<char> set_letters{ 'a', 'b', 'c', 'd' };
	vector<char> guesses{}; // initialize as empty
	cout << "Guess " << set_letters.size() << " letters in the range of a - z to guess what I have.\n";
	cout << "If guess a correct letter and the correct location will get a Bull.\n";
	cout << "If guess a correct letter but not the correct location then will get a Cow.\n";
	cout << "Example: My set is abcd and your guess was acbe, so there are 2 Cows (b and c)  1 Bull (a).\n\n";
	cout << "Enter your guess.  To quit enter |.\n";
	bool status = true;
	while (status)
	{
		status = get_guesses(guesses, set_letters.size());

		if (status && guesses == set_letters) {
			cout << "You have " << set_letters.size() << " Bulls, Congratulations!\n";
			status = false;
		}
		else if (status) {
			vector<char> scratch = set_letters;
			int bulls = get_bulls(guesses, scratch);
			int cows = get_cows(guesses, scratch);
			cout << "The result is " << cows << (cows == 1 ? " Cow" : " Cows")
				 << " and " << bulls << (bulls == 1 ? " Bull" : " Bulls") << ". Try again.\n";
			guesses = {}; // clear for new set of guesses
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
/* function to get user input for letters a - z.
INPUT: vector<char> reference to place valid guesses in.
       int for how many guesses needed
OUPUT: bool true = got valid integers placed into the vector of int size
       bool false = got early termination.
ERROR: if given reference vector is not empty.
*/
bool get_guesses(vector<char>&input, const unsigned x)
{
	if (!input.empty()) {
		error("Function get_guesses() reference to vector not empty.\n");
	}
	while(true) {
		char guess = '|';
		cin >> guess;
		if (isalpha(guess) || guess == '|') { //check for valid number or escape entry
			if (guess == '|') {
				return false; // found a termination
			}
			else { //convert number char to integer and place into a vector
				input.push_back(guess);
				if (input.size() == x) { //checks if have correct number of guesses
					return true; // got all guesses
				}
			}
		}
		else { //bad entry clear vector and purge input buffer
			cout << "bad entry try again.\n";
			input.clear();
			cin.ignore(INT8_MAX, '\n');
		}
	}
}

/* function to bulls.
INPUT: vector<char> reference to user input guesses.
       vector<char> reference to number to guess.
OUPUT: int for number of bulls found
ERROR: no error.
modifies the temp vector by placing ? when finds a bull
*/
int get_bulls(const vector<char>&g, vector<char>&temp)
{
	int bulls = 0;
	for (auto itrg = begin(g); itrg != end(g); ++itrg) {
		for (auto itrt = begin(temp); itrt != end(temp); ++itrt)  //find Bulls
		{
			itrt = find(itrt, end(temp), *itrg);
			if (itrt == end(temp)) {
				break;
			}
			else if ((itrt - begin(temp)) == (itrg - begin(g))) {
				++bulls;
				*itrt = '?';
				break;
			}
		}
	}
	return bulls;
}

/* function to cows.
INPUT: vector<char> reference to user input guesses.
       vector<char> reference to number to guess.
OUPUT: int for number of cows found
ERROR: no error.
modifies the temp vector by placing ? when finds a cow
*/
int get_cows(const vector<char>&g, vector<char>&temp)
{
	int cows = 0;
	for (auto itrg = begin(g); itrg != end(g); ++itrg) {
		for (auto itrt = begin(temp); itrt != end(temp); ++itrt)  //find Cows
		{
			itrt = find(itrt, end(temp), *itrg);
			if (itrt == end(temp)) {
				break;
			}
			else {
				++cows;
				*itrt = '?';
				break;
			}
		}
	}
	return cows;
}