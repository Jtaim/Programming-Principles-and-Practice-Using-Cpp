#ifndef TOKEN_H	// begin header guard
#define TOKEN_H

#include "symbol_table.hpp"
#include <istream>
#include <string>

namespace calculator
{

    constexpr char number = '8';                        // t.kind == number means that t is a number Token.
    constexpr char quit = 'q';                          // t.kind == quit means that t is a quit Token.
    constexpr std::string_view declquit = "quit";       // quit keyword
    constexpr char print = ';';                         // t.kind == print means that t is a print Token.
    constexpr char newline = '\n';                      // t.kind == newline sets token to print Token.
    constexpr char name = 'a';                          // t.kind == name token
    constexpr char let = 'L';                           // declaration token
    constexpr char clet = 'C';                          // constant declaration token
    constexpr std::string_view declkey = "let";         // declaration keyword
    constexpr std::string_view constdeclkey = "const";  // constant declaration keyword
    constexpr char func = 'F';                          // function Token
    constexpr char help = 'h';                          // t.kind == help means that t is a help Token.
    constexpr std::string_view declhelp = "help";       // help keyword

    //------------------------------------------------------------------------------

    struct Token
    {
        char kind{};
        double value{};
        std::string name;

        //constructors
        Token() = default;
        Token( char ch ) : kind{ ch }, value{} {}
        Token( char ch, double val ) : kind{ ch }, value{ val } {}
        Token( char ch, std::string s ) : kind{ ch }, value{}, name{ s } {}
    };

    //------------------------------------------------------------------------------

    class Token_Stream
    {
    public:
        Token_Stream() = default;
        Token_Stream( std::istream& tsin ); // Token_stream that reads from an istream
        Token get();                        // get a Token to place in the stream
        void putback( const Token t );      // put a Token back
        void ignore( const char c );        // discard characters up to and including the given input kind token

        Symbol_Table symbol_table;

    private:
        bool full{};                        // is there a Token in the buffer?
        Token buffer{ 0 };                  // here is where we keep a Token put back using putback()
    };

} // calculator

#endif	// close header guard