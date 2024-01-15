//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 10.
 Write a program that plays the game “Rock, Paper, Scissors.”
 If you are not familiar with the game do some research (e.g., on the web using Google).
 Research is a common task for programmers. Use a switch-statement to solve this exercise.
 Also, the machine should give random answers (i.e., select the next rock, paper, or scissors randomly).
 Real randomness is too hard to provide just now, so just build a vector with a sequence of values to be
 used as “the next value.” If you build the vector into the program, it will always play the same game,
 so maybe you should let the user enter some values.
 Try variations to make it less easy for the user to guess which move the machine will make next.
*/

#include "section4.hpp"

constexpr auto rps = std::to_array<std::string_view>( { "rock", "paper", "scissors" } );

static int getSelection()
{
    std::string input;
    int number{};
    if( std::cin >> input && input.size() == 1 && std::isdigit( static_cast<unsigned char>( input[0] ) ) )
    {
        number = atoi( input.data() ) - 1;  // minus one to get proper index from rps[]
        if( number < 0 || number > 2 )
        {
            simple_error( std::format( "{} is an invalid selection", input ) );
        }
    }
    // check if number is spelled out
    else
    {
        std::for_each( input.begin(), input.end(), []( auto& c ) { c = static_cast<char>( tolower( static_cast<unsigned char>( c ) ) ); } );

        // check if has a spelled out number
        auto spelledIndex = std::find( rps.begin(), rps.end(), input );
        if( spelledIndex != rps.end() )
        {
            number = static_cast<int>( spelledIndex - rps.begin() );
        }
        else
        {
            simple_error( std::format( "{} is an invalid selection", input ) );
        }
    }
    return number;
}
int main()
{
    //Will be used to obtain a seed for the random number engine
    std::random_device rd;
    //Standard mersenne_twister_engine seeded with rd()
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> dis( 0, 2 );


    bool playAgain{ false };
    do
    {
        std::cout << "Select (1)Rock (2)Paper (3)Scissors ";
        // get players input
        int playersSelection{ getSelection() };
        // get computer input
        int computersSelection{ dis( gen ) };  //have only 3 selections gets random selection between 0 and 2

        std::cout << std::format( "Your selection was {} the computer selected was {}",
                                  rps.at( playersSelection ), rps.at( computersSelection ) ) << std::endl;

        std::cout << "The winner is ";
        switch( playersSelection )
        {
            case 0:
                std::cout << ( computersSelection == 0 ? "a tie" : computersSelection == 2 ? "player" : "computer" ) << std::endl;
                break;
            case 1:
                std::cout << ( computersSelection == 1 ? "a tie" : computersSelection == 0 ? "player" : "computer" ) << std::endl;
                break;
            case 2:
                std::cout << ( computersSelection == 2 ? "a tie" : computersSelection == 1 ? "player" : "computer" ) << std::endl;
                break;
            default:
                // should never reach this state with previous if statement
                break;
        }

        std::cout << "\nWould you like to play again (y or n)" << std::endl;
        char c;
        std::cin >> c;
        // check for proper input
        c == 'y' ? playAgain = true : playAgain = false;
    } while( playAgain );

    keep_window_open();
    return 0;
}
