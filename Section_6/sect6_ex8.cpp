//Written by Jtaim
//Date 1 Dec 2015
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 6 exercise 8
Rewrite Section 5 exercise 12 Bulls and Cows game to use 4 letters not 4 numbers.
*/

#include "section6.h"
bool get_guesses(std::vector<char>& input, const size_t x, const char term = '|');
int get_bulls(std::vector<char>&, std::vector<char>&);
int get_cows(std::vector<char>&, std::vector<char>&);

int main()
{
    try
    {
        using std::cout;

        const char TERM = '|';

        std::vector<char> set_letters{ 'a', 'b', 'c', 'd' };
        std::vector<char> guesses{};
        cout << "Guess " << set_letters.size() << " letters in the range of a - z to guess what I have.\n";
        cout << "If guess a correct letter and the correct location will get a Bull.\n";
        cout << "If guess a correct letter but not the correct location then will get a Cow.\n";
        cout << "Example: My set is abcd and your guess was acbe, so there are 2 Cows (b and c)  1 Bull (a).\n\n";
        cout << "Enter your guess.  To quit enter |.\n";

        while (get_guesses(guesses, set_letters.size(), TERM))
        {
            if (guesses == set_letters)
            {
                cout << "You have " << set_letters.size() << " Bulls, Congratulations!\n";
                break;
            }
            else
            {
                std::vector<char> scratch = set_letters;
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
}
/* function to get user input for letters a - z.
INPUT: vector<char> reference to place valid guesses in.
       int for how many guesses needed
OUPUT: bool true = got valid char placed into the vector of int size
       bool false = got early termination.
ERROR: none
*/
bool get_guesses(std::vector<char> &input, const size_t x, const char term)
{
    if (!input.empty())
    {
        input.clear();
    }
    char guess;
    auto itr = x;
    bool guess_qualified = true;
    while (guess_qualified && itr > 0)
    {
        std::cin >> guess;
        //check for valid number or escape entry
        if (guess == term)
        {
            guess_qualified = false;
        }
        else if (isalpha(guess))
        {	//check for valid number or escape entry
            guess = static_cast<char>(tolower(guess));
            input.push_back(guess);
            --itr;
        }
        else
        {	//bad entry clear vector and purge input buffer
            std::cout << "bad entry try again.\n";
            std::cin.clear();
            std::cin.ignore(INT16_MAX, '\n');
            input.clear();
            itr = x;
        }
    }
    return guess_qualified;
}

/* function to bulls.
INPUT: vector<char> reference to user input guesses.
       vector<char> reference to number to guess.
OUPUT: int for number of bulls found
ERROR: no error.
modifies the vectors by deleting matching elements
*/
int get_bulls(std::vector<char> &g, std::vector<char> &temp)
{
    int bulls = 0;
    // be careful of rollover of unsigned i
    for (auto i = g.size(); i > 0; --i)
    {
        //find Bulls starting from back 
        //if find match erase elements from back to front
        //do back to front so don't cause error from going outside vector bounds
        //adjust i from size to element (i-1)
        if (g[i - 1] == temp[i - 1])
        {
            temp.erase(temp.begin() + i - 1);
            g.erase(g.begin() + i - 1);
            ++bulls;
        }
    }
    return bulls;
}

/* function to cows.
INPUT: vector<char> reference to user input guesses.
       vector<char> reference to number to guess.
OUPUT: int for number of cows found
ERROR: no error.
delete vector temp matching elements to vector g
*/
int get_cows(std::vector<char> &g, std::vector<char> &temp)
{
    int cows = 0;
    for (auto i : g)
    {
        //find Cows
        if (!temp.empty())
        {
            auto pos = find(begin(temp), end(temp), i);
            if (pos != end(temp))
            {
                temp.erase(pos);
                ++cows;
            }
        }
    }
    return cows;
}
