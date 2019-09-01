//Written by Jtaim
//Date 1 Dec 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 8
Rewrite Section 5 exercise 12 Bulls and Cows game to use 4 letters not 4 numbers.
*/

#include "section6.h"

using vType = std::vector<char>;
bool get_guesses(vType& input, const char term);
int get_bulls(const vType& guesses, vType& setSequence);
int get_cows(const vType& guesses, vType& setSequence);
const vType::value_type foundMark = '?';

int main()
{
	try{
		using std::cout;

		const char termination = '|';

		vType const setLetters{'a', 'b', 'c', 'd'};
		vType guesses{};
		guesses.reserve(setLetters.size());

		cout << "Guess " << setLetters.size() << " letters in the range of a - z to guess what I have.\n";
		cout << "If guess a correct letter and the correct location will get a Bull.\n";
		cout << "If guess a correct letter but not the correct location then will get a Cow.\n";
		cout << "Example: My set is abcd and your guess was acbe, so there are 2 Cows (b and c)  1 Bull (a).\n\n";
		cout << "Enter your guess.  To quit enter |.\n";

		while(get_guesses(guesses, termination)){
			if(guesses == setLetters){
				std::cout << "You have " << setLetters.size() << " Bulls, Congratulations!\n";
				break;
			} else{
				auto temp = setLetters;
				auto bulls = get_bulls(guesses, temp);
				auto cows = get_cows(guesses, temp);

				std::cout << "The result is " << cows << (cows == 1 ? " Cow" : " Cows");
				std::cout << " and " << bulls << (bulls == 1 ? " Bull" : " Bulls") << ". Try again.\n";
				guesses.clear();	// clear for new set of guesses
			}
		}

		cout << "Bye\n";
		keep_window_open();
		return 0;
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
}
/* function to get user input for letters a - z.
INPUT:  vType reference to place valid guesses in.
OUPUT:  bool true = got valid guesses
		bool false = got valid termination.
ERROR: invalid guess or termination.
*/
bool get_guesses(vType& input, const char term)
{
	for(vType::size_type itr = 0; itr < input.capacity(); ++itr){
		char guess{};
		std::cin >> guess;
		//check for valid number or escape entry
		if(guess == term){
			return false;
		}
		//convert number char to integer and place into a vector
		else if(isalpha(guess)){
			vType::value_type i = guess;
			input.push_back(i);
		} else{
			error("Bad entry data!");
		}
	}
	return !input.empty();
}

/* function to bulls.
INPUT: vType reference to user input guesses.
	   vType reference to number to guess.
OUPUT: int for number of bulls found
ERROR: no error.
modifies set sequence by setting matching elements to type max number
*/
int get_bulls(const vType& guesses, vType& setSequence)
{
	int bulls{};
	auto j{setSequence.begin()};
	for(auto i{guesses.cbegin()}; i < guesses.cend(); ++i, ++j){
		if(*i == *j){
			++bulls;
			*j = foundMark;
		}
	}
	return bulls;
}

/* function to cows.
INPUT: vType reference to user input guesses.
	   vType reference to number to guess.
OUPUT: int for number of cows found
ERROR: no error.
modifies set sequence by setting matching elements to type max number
*/
int get_cows(const vType& guesses, vType& setSequence)
{
	int cows{};
	for(auto j{setSequence.begin()}; j < setSequence.end(); ++j){
		for(auto i{guesses.cbegin()}; i < guesses.cend(); ++i){
			if(*i == *j){
				++cows;
				*j = foundMark;
				break;
			}
		}
	}
	return cows;
}
