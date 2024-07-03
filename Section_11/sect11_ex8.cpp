/*
    Written by Jtaim
    Date 28 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 8
    Write a program that replaces punctuation with whitespace.
    Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters.
    Don’t modify characters within a pair of double quotes (").
    For example, " - don't use the as-if rule." becomes " don t use the as if rule ".

    Modify the program from the previous exercise so that it replaces don't with do not, can't with cannot, etc.;
    leaves hyphens within words intact (so that we get “ do not use the as-if rule ”); and converts all characters to lower case.
    https://en.wikipedia.org/wiki/Contraction_(grammar)
    https://www.grammarly.com/blog/contractions/
    https://grammar.yourdictionary.com/style-and-usage/using-contractions.html
    https://www.thoughtco.com/contractions-commonly-used-informal-english-1692651

    Use the program from the previous exercise to make a dictionary (as an alternative to the approach in Section 11.7).
    Run the result on a multi-page text file, look at the result, and see if you can improve the program to make a better dictionary.
*/

#include "ppp.hpp"
#include "Punct_stream.hpp"

std::unordered_map<std::string, std::string> contractions{
    {"aren't", "are not"},
    {"can't", "cannot"},
    {"couldn't", "could not"},
    {"could've", "could have"},
    {"didn't", "did not"},
    {"doesn't", "does not"},
    {"don't", "do not"},
    {"hadn't", "had not"},
    {"hasn't", "has not"},
    {"haven't", "have not"},
    {"i'm", "i am"},
    {"i've", "i have"},
    {"isn't", "is not"},
    {"let's", "let us"},
    {"shan't", "shall not"},
    {"shouldn't", "should not"},
    {"should've", "should have"},
    {"they're", "they are"},
    {"they've", "they have"},
    {"wasn't", "was not"},
    {"we'll", "we will"},
    {"we're", "we are"},
    {"we've", "we have"},
    {"weren't", "were not"},
    {"who've", "who have"},
    {"won't", "will not"},
    {"wouldn't", "would not"},
    {"would've", "would have"},
    {"you're", "you are"},
    {"you've", "you have"}
};

int main()
// given text input, produce a sorted list of all words in that text
// ignore punctuation and case differences
// eliminate duplicates from the output
try
{
    Punct_stream ps{ std::cin };                    // ps reads from cin
    //ps.whitespace( ";:,.?!()\"{}<>/&$@#%^*|~" );    // note \“ means ” in string
    ps.case_sensitive( false );

    std::cout << "Please enter words\n";
    std::vector<std::string> vs;
    for( std::string word; ps >> word; )            // read words
    {
        auto index{ contractions.find( word ) };
        if( index != contractions.end() )
        {
            std::istringstream ct{ index->second };
            while( ct >> word )
            {
                vs.push_back( word );
            }
        }
        vs.push_back( word );
    }
    std::sort( vs.begin(), vs.end() );              // sort in lexicographical order
    for( std::size_t i{}; i < vs.size(); ++i )      // write dictionary
    {
        if( i == 0 || vs.at( i ) != vs.at( i - 1 ) )
        {
            std::cout << vs.at( i ) << '\n';
        }
    }

ppp::keep_window_open();
return 0;
}
catch( std::exception &e )
{
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch( ... )
{
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}
