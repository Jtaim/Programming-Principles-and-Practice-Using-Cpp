//written by Jtaim
//date 8 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 13
Bulls and Cows game.
random generate the numbers to guess
Guess the 4 numbers range(0 to 9)
*/


#include "section5.h"
bool get_guesses(std::vector<int>&input, const size_t x, const char term = '|');
int get_bulls(std::vector<int>&, std::vector<int>&);
int get_cows(std::vector<int>&, std::vector<int>&);
bool try_again(const std::string&);

int main()
try
{
    using std::cout;

    const char termination = '|';
    const int guessSize = 4;  // sets how many numbers to guess

    cout << "Guess " << guessSize << " numbers in the range of 0 - 9 to guess what I have.\n";
    cout << "If guess a correct number and the correct location will get a Bull.\n";
    cout << "If guess a correct number but not the correct location then will get a Cow.\n";
    cout << "Example: My set is 2345 and your guess was 5248, so there are 2 Cows (5 and 2)  1 Bull (4).\n\n";
    std::vector<int> set_numbers;
    std::vector<int> guesses;
    do
    {
        cout << "Enter your guess.  To quit enter '" << termination << "'.\n\n";
        // set initial seed value to system clock i know conversion warning but don't care
        srand(narrow_cast<unsigned>(time(nullptr)));
        // create random guess_size numbers
        for (int i = 0; i < guessSize; ++i) {
            set_numbers.push_back(rand() % 10);
        }
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
        guesses.clear();		// reset vectors
        set_numbers.clear();
    } while (try_again("Would you like to try again (y or n).\n"));
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
INPUT:	vector<int> reference to place valid guesses in.
        int for how guesses needed
OUPUT:	bool true = got valid integers placed into the vector of int size
        bool false = got early termination.
ERROR:	find non numeric entry other than the termination character
        cin failure bad()
        entry < 0 or entry > 9
*/
bool get_guesses(std::vector<int>&input, const size_t x, const char term)
{
    if (!input.empty()) {
        input.clear();
    }
    int guess;
    auto itr = x;
    bool guess_qualified = true;
    while (itr > 0) {
        //check for valid number or escape entry
        if (!(std::cin >> guess)) {
            if (std::cin.bad()) {
                error("cin.bad() flag set when getting guesses");
            }
            std::cin.clear();
            //check for valid escape entry
            if (std::cin.get() == term) {
                guess_qualified = false;
                break;
            }
            else {
                error("guess entry is non-numeric");

            }
        }
        //check that number is valid 
        else if (guess >= 0 && guess <= 9) {
            input.push_back(guess);
            --itr;
        }
        else {
            error("entry < 0 or entry > 9");
        }
    }
    return guess_qualified;
}

/* function to bulls.
INPUT:	vector<int> reference to user input guesses.
        vector<int> reference to number to guess.
OUPUT:	int for number of bulls found
ERROR:	no error.
modifies the vectors by deleting matching elements
*/
int get_bulls(std::vector<int>& g, std::vector<int>& temp)
{
    int bulls = 0;
    // be careful of rollover of unsigned i
    for (auto i = g.size(); i > 0; --i) {
        //find Bulls starting from back 
        //if find match erase elements from back to front
        //do back to front to avoid outside vector bounds exception
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
/* function to get user input for a yes or no answer.
INPUT: string for message you want displayed.
OUPUT: bool
ERROR: wrong selection bad user input.
*/
bool try_again(const std::string &s)
{
    std::cout << s;
    char again = '?';
    std::cin >> again;
    again = static_cast<char>(tolower(again));
    if (again == 'n') {
        std::cout << "Thanks for playing, goodbye.\n\n";
        return false;
    }
    else if (again == 'y') {
        return true;
    }
    else {
        error("Oops: really can't enter y or n!\n");
        return false;
    }
}
