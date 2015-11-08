//written by Jtaim
//date 7 Nov 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 12
Bulls and Cows game.
Guess the 4 numbers range(0 to 9)
*/


#include "section5.h"
bool get_guesses(vector<int>&, const unsigned);
int get_bulls(const vector<int>&, vector<int>&);
int get_cows(const vector<int>&, vector<int>&);
bool try_again(const string&);

int main()
try
{

	const int guess_size = 4;  // sets how many numbers to guess
	cout << "Guess " << guess_size << " numbers in the range of 0 - 9 to guess what I have.\n";
	cout << "If guess a correct number and the correct location will get a Bull.\n";
	cout << "If guess a correct number but not the correct location then will get a Cow.\n";
	cout << "Example: My set is 2345 and your guess was 5248, so there are 2 Cows (5 and 2)  1 Bull (4).\n\n";
	do
	{
		cout << "Enter your guess.  To quit enter |.\n\n";
		vector<int> guesses{}; // initialize as empty
		vector<int> set_numbers{};
		srand(time(0)); // set initial seed value to system clock i know conversion warning but don't care
		for (int i = 0; i < guess_size; ++i) { // create random guess_size numbers
			set_numbers.push_back(rand() % 10);
		}
		bool status = true;
		while (status)
		{
			status = get_guesses(guesses, set_numbers.size());

			if (status && guesses == set_numbers) {
				cout << "You have " << set_numbers.size() << " Bulls, Congratulations!\n";
				status = false;
			}
			else if (status) {
				vector<int> scratch = set_numbers;
				int bulls = get_bulls(guesses, scratch);
				int cows = get_cows(guesses, scratch);
				cout << "The result is " << cows << (cows == 1 ? " Cow" : " Cows")
					<< " and " << bulls << (bulls == 1 ? " Bull" : " Bulls") << ". Try again.\n";
				guesses = {}; // clear for new set of guesses
			}
		}
	} while (try_again("Would you like to try again (y or n).\n"));
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

/* function to get user input for integer numbers.
INPUT: vector<int> reference to place valid guesses in.
       int for how guesses needed
OUPUT: bool true = got valid integers placed into the vector of int size
       bool false = got early termination.
ERROR: if given reference vector is not empty.
*/
bool get_guesses(vector<int>&input, const unsigned x)
{
	if (!input.empty()) {
		error("Function get_guesses() reference to vector not empty.\n");
	}
	while (true) {
		char guess = '|';
		cin >> guess;
		if (isdigit(guess) || guess == '|') { //check for valid number or escape entry
			if (guess == '|') {
				return false; // found a termination
			}
			else { //convert number char to integer and place into a vector
				int i = guess - '0'; // so '0'(48) threw '9'(57) - '0'(48) = a number 0 to 9
				input.push_back(i);
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

/* function to get bulls.
INPUT: vector<int> reference to user input guesses.
       vector<int> reference to number to guess.
OUPUT: int for number of bulls found
ERROR: no error.
modifies the temp vector by placing -1 when finds a bull
*/
int get_bulls(const vector<int>&g, vector<int>&temp)
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
				*itrt = -1;
				break;
			}
		}
	}
	return bulls;
}

/* function to get cows.
INPUT: vector<int> reference to user input guesses.
       vector<int> reference to number to guess.
OUPUT: int for number of cows found
ERROR: no error.
modifies the temp vector by placing -1 when finds a cow
*/
int get_cows(const vector<int>&g, vector<int>&temp)
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
				*itrt = -1;
				break;
			}
		}
	}
	return cows;
}

/* function to get user input for a yes or no answer.
INPUT: string for message you want displayed.
OUPUT: bool
ERROR: wrong selection bad user input.
*/
bool try_again(const string &s)
{
	cout << s;
	char again = '?';
	cin >> again;
	tolower(again);
	if (again == 'n') {
		cout << "Thanks for playing, goodbye.\n\n";
		return false;
	}
	else if (again == 'y')
		return true;
	else {
		error("Oops: really can't enter y or n!\n");
		return false;
	}
}