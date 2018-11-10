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
using vType = std::vector<int>;
bool get_guesses(vType&input, const char term);
int get_bulls(const vType& guesses, vType &setSequence);
int get_cows(const vType& guesses, vType &setSequence);
bool try_again(const std::string&);

int main()
try
{
    const char termination = '|';
    const int guessSize = 4;  // sets how many numbers to guess
    vType setNumbers;
    setNumbers.reserve(guessSize);
    vType guesses{};
    guesses.reserve(guessSize);

    std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);

    std::cout << "Guess " << guessSize << " numbers in the range of 0 - 9 to guess what I have.\n";
    std::cout << "If guess a correct number and the correct location will get a Bull.\n";
    std::cout << "If guess a correct number but not the correct location then will get a Cow.\n";
    std::cout << "Example: My set is 2345 and your guess was 5248, so there are 2 Cows (5 and 2)  1 Bull (4).\n\n";

    do
    {
        std::cout << "Enter your guess.  To quit enter '" << termination << "'.\n\n";
        //Will be used to obtain a seed for the random number engine

        // create random guess_size numbers
        for (int i = 0; i < guessSize; ++i) {
            setNumbers.push_back(dis(gen));
        }

        while (get_guesses(guesses, termination)) {
            if (guesses == setNumbers) {
                std::cout << "You have " << setNumbers.size() << " Bulls, Congratulations!\n";
                break;
            }
            else {
                auto temp = setNumbers;
                auto bulls = get_bulls(guesses, temp);
                auto cows = get_cows(guesses, temp);

                std::cout << "The result is " << cows << (cows == 1 ? " Cow" : " Cows");
                std::cout << " and " << bulls << (bulls == 1 ? " Bull" : " Bulls") << ". Try again.\n";
                guesses.clear();	// clear for new set of guesses
            }
        }

        guesses.clear();		// reset vectors
        setNumbers.clear();
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

/* function to get user input for guesses or termination.
INPUT:  vType reference to place valid guesses in.
OUPUT:  bool true = got valid guesses
        bool false = got valid termination.
ERROR: invalid guess or termination.
*/
bool get_guesses(vType&input, const char term)
{
    for (vType::size_type itr{}; itr < input.capacity(); ++itr) {
        char guess{};
        std::cin >> guess;
        //check for valid number or escape entry
        if (guess == term) {
            return false;
        }
        //convert number char to integer and place into a vector
        else if (isdigit(guess)) {
            vType::value_type i = guess - '0'; // '9'(57) - '0'(48) provides 0 to 9
            input.push_back(i);
        }
        else {
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
int get_bulls(const vType& guesses, vType &setSequence)
{
    int bulls{};
    auto j{ setSequence.begin() };
    for (auto i{ guesses.cbegin() }; i < guesses.cend(); ++i, ++j) {
        if (*i == *j) {
            ++bulls;
            *j = std::numeric_limits<vType::value_type>::max();
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
int get_cows(const vType &guesses, vType &setSequence)
{
    int cows{};
    for (auto j{ setSequence.begin() }; j < setSequence.end(); ++j) {
        for (auto i{ guesses.cbegin() }; i < guesses.cend(); ++i) {
            if (*i == *j) {
                ++cows;
                *j = std::numeric_limits<vType::value_type>::max();
                break;
            }
        }
    }
    return cows;
}

/* function to get user input for a yes or no answer.
INPUT: string for message you want displayed.
OUPUT: bool
ERROR: none
*/
bool try_again(const std::string &s)
{
    std::cout << s;
    char again{};
    std::cin >> again;
    again = narrow_cast<char, int>(tolower(again));
    if (again == 'y') {
        return true;
    }
    std::cout << "Thanks for playing, goodbye.\n\n";
    return false;
}
