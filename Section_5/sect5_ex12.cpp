//written by Jtaim
//date 8 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 12
Bulls and Cows game.
Guess the 4 numbers range(0 to 9)
*/

#include "section5.h"

using vType = std::vector<int>;
static bool get_guesses( vType& input, std::size_t length );
static int get_bulls( vType& guesses, vType& set_sequence );
static int get_cows( vType& guesses, vType& set_sequence );
static const vType::value_type found_mark = std::numeric_limits<vType::value_type>::max();

int main()
try
{
    vType const set_numbers{2, 5, 8, 1};
    //vType const set_numbers{ 5, 7, 8, 0 };
    //vType const set_numbers{2, 2, 2, 2};
    vType guesses{};

    std::cout << "Guess " << set_numbers.size() << " numbers in the range of 0 - 9 to guess what I have.\n";
    std::cout << "If guess a correct number and the correct location will get a Bull.\n";
    std::cout << "If guess a correct number but not the correct location then will get a Cow.\n";
    std::cout << "Example: My set is 2345 and your guess was 5248, so there are 2 Cows (5 and 2)  1 Bull (4).\n\n";
    std::cout << "Enter your guess.\n";

    while( get_guesses( guesses, set_numbers.size() ) )
    {
        if( guesses == set_numbers )
        {
            std::cout << std::format("You have {} Bulls, Congratulations!\n", set_numbers.size());
            break;
        }
        else
        {
            vType numbers = set_numbers;
            auto bulls = get_bulls( guesses, numbers );
            auto cows = get_cows( guesses, numbers );

            std::cout << std::format("The result is {} {} and {} {}. Try again.\n",
                                      cows, ( cows == 1 ? "Cow" : "Cows" ),
                                      bulls, ( bulls == 1 ? "Bull" : "Bulls" ));
            guesses.clear();	// clear for new set of guesses
        }
    }

    std::cout << "Bye\n";
    keep_window_open();
    return 0;
}
catch( std::exception& e )
{
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}

/* function to get user input for guesses.
INPUT: vector reference to store guesses.
       size_t for length of number to guess.
OUPUT: bool true = got valid guesses
       bool false = insufficient guess entered.
ERROR: invalid guess.
*/
bool get_guesses( vType& input, std::size_t length )
{
    std::string user_guess;
    std::cin >> user_guess;

    if( user_guess.size() != length )
    {
        std::cout << std::format("Number of guesses entered must be {} digits\n", length);
        return false;
    }

    for( unsigned char guess : user_guess )
    {
        // convert number char to integer and place into a vector
        if( isdigit( guess ) )
        {
            // '9'(57) - '0'(48) provides 0 to 9
            vType::value_type number = guess - '0';
            input.push_back( number );
        }
        else
        {
            error( "guess is not valid!" );
        }
    }
    return true;
}

/* function to bulls.
INPUT: vType reference to user input guesses.
       vType reference to number to guess.
OUPUT: int for number of bulls found
ERROR: input vector sizes do not match.
modifies guesses by setting matching elements to type max number
*/
int get_bulls( vType& guesses, vType& set_sequence )
{
    if( guesses.size() != set_sequence.size() )
    {
        error( "guess and answer size do not match!" );
    }

    int bulls{};
    for( auto i{ guesses.begin() }, j{ set_sequence.begin() }; i < guesses.cend(); ++i, ++j )
    {
        if( *i == *j )
        {
            ++bulls;
            *i = *j = found_mark;
        }
    }
    return bulls;
}

/* function to cows.
INPUT: vType reference to user input guesses.
       vType reference to number to guess.
OUPUT: int for number of cows found
ERROR: input vector sizes do not match.
modifies guesses by setting matching elements to type max number
*/
int get_cows( vType& guesses, vType& set_sequence )
{
    if( guesses.size() != set_sequence.size() )
    {
        error( "input vector sizes do not match!" );
    }

    int cows{};
    for( auto& guess : guesses )
    {
        if( guess != found_mark )
        {
            auto itr = std::find( set_sequence.begin(), set_sequence.end(), guess );
            if( itr != set_sequence.cend() )
            {
                ++cows;
                guess = *itr = found_mark;
            }
        }
    }
    return cows;
}
