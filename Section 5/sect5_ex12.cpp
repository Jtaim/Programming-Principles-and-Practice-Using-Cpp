//written by Jtaim
//date 8 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 12
Bulls and Cows game.
Guess the 4 numbers range(0 to 9)
*/

#include "section5.h"
bool get_guesses(std::vector<int>&input, const size_t x, const char term = '|');
int get_bulls(std::vector<int>&, std::vector<int>&);
int get_cows(std::vector<int>&, std::vector<int>&);

int main()
try
{
	using std::cout;

	const char termination = '|';

	std::vector<int> const set_numbers{ 2, 5, 8, 1 };
	std::vector<int> guesses{};					// initialize as empty
	cout << "Guess " << set_numbers.size() << " numbers in the range of 0 - 9 to guess what I have.\n";
	cout << "If guess a correct number and the correct location will get a Bull.\n";
	cout << "If guess a correct number but not the correct location then will get a Cow.\n";
	cout << "Example: My set is 2345 and your guess was 5248, so there are 2 Cows (5 and 2)  1 Bull (4).\n\n";
	cout << "Enter your guess.  To quit enter '" << termination << "'.\n";

	while (get_guesses(guesses, set_numbers.size(), termination)) {
		if (guesses == set_numbers) {
			cout << "You have " << set_numbers.size() << " Bulls, Congratulations!\n";
			break;
		}
		else {
			std::vector<int> scratch = set_numbers;
			int bulls = get_bulls(guesses, scratch);
			int cows = get_cows(guesses, scratch);
			cout << "The result is " << cows << (cows == 1 ? " Cow" : " Cows");
			cout << " and " << bulls << (bulls == 1 ? " Bull" : " Bulls") << ". Try again.\n";
			guesses.clear();	// clear for new set of guesses
		}
	}
	cout << "Bye\n";
	keep_window_open();
	return 0;
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
/* function to get user input for integer numbers.
INPUT: vector<int> reference to place valid guesses in.
       int for how guesses needed
OUPUT: bool true = got valid integers placed into the vector of int size
       bool false = got early termination.
ERROR: if given reference vector is not empty.
*/
bool get_guesses(std::vector<int>&input, const size_t x, const char term)
{
	if (!input.empty()) {
		input.clear();
	}
	char guess;
	auto itr = x;
	bool guess_qualified = true;
	while (itr > 0) {
		std::cin >> guess;
		//check for valid number or escape entry
		if (guess == term) {
			guess_qualified = false;
			break;
		}
		//convert number char to integer and place into a vector
		else if (isdigit(guess)) {
			int i = guess - '0'; // so '0'(48) threw '9'(57) - '0'(48) = a number 0 to 9
			input.push_back(i);
			--itr;
		}
		//bad entry clear vector and purge input buffer
		else {
			std::cout << "bad entry try again.\n";
			guess_qualified = false;
			break;
		}
	}
	return guess_qualified;
}

/* function to bulls.
INPUT: vector<int> reference to user input guesses.
       vector<int> reference to number to guess.
OUPUT: int for number of bulls found
ERROR: no error.
modifies the vectors by deleting matching elements
*/
int get_bulls(std::vector<int>& g, std::vector<int>& temp)
{
	int bulls = 0;
	// be carefull of rollover of unsigned i
	for (auto i = g.size(); i > 0; --i) {
		//find Bulls starting from back 
		//if find match erase elements from back to front
		//do back to front so dont cause error from going outside vector bounds
		//adjust i from size to element (i-1)
		if (g[i - 1] == temp[i - 1]) {
			temp.erase(temp.begin() + i - 1);
			g.erase(g.begin() + i - 1);
			++bulls;
		}
	}
	return bulls;
}

/* function to cows.
INPUT: vector<int> reference to user input guesses.
       vector<int> reference to number to guess.
OUPUT: int for number of cows found
ERROR: no error.
delete vector temp matching elements to vector g
*/
int get_cows(std::vector<int>& g, std::vector<int>& temp)
{
	int cows = 0;
	for (auto i : g) {
		//find Cows
		if (!temp.empty()) {
			auto pos = find(begin(temp), end(temp), i);
			if (pos != end(temp)) {
				temp.erase(pos);
				++cows;
			}
		}
	}
	return cows;
}
