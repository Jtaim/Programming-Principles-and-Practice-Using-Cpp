//written by Jtaim
//date 26 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 Try This 4.6.4
Write a program that "bleeps" out words that you don't like; that is,
you read in words using cin and print them again on cout.
If a word is among a few you have defined, you write out BLEEP instead of that word.
Start with one "disliked word" such as
string disliked = "Broccoli";
When that works, add a few more.
*/

#include "section4.hpp"

//list of disliked words
constexpr auto dislikedWords = std::to_array<std::string_view>( { "broccoli", "peas", "spinach" } );

std::string bleep_disliked_word( const std::string& s )
{
    std::string temp = s;
    std::for_each( temp.begin(), temp.end(),
                   []( char& c ) { c = static_cast<char>( std::tolower( static_cast<unsigned char>( c ) ) ); } );
    if( std::find( dislikedWords.cbegin(), dislikedWords.cend(), temp ) != dislikedWords.cend() )
    {
        return "\aBLEEP";
    }
    return s;
}

int main()
{
    std::vector<std::string> words;
    // read whitespace-separated words
    for( std::string word; std::cin >> word && word != "quit"; )
    {

        words.push_back( word );	// put into vector
    }

    std::cout << "Number of words: " << words.size() << std::endl;
    for( const auto& str : words )
    {
        std::cout << bleep_disliked_word( str ) << " ";
    }
    std::cout << std::endl;

    keep_window_open();
    return 0;
}
