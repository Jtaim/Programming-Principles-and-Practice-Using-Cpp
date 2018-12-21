#ifndef TOKEN_H	// begin header guard
#define TOKEN_H

#include <string>

namespace calculator
{

    const char number = '8';                // t.kind == number Token.
    const char print = ';';                 // t.kind == print Token.

    const char quit = 'q';                  // t.kind == quit Token.                                     
    const std::string key_quit = "quit";    // quit keyword
    const char help = 'h';                  // t.kind == help Token.
    const std::string key_help = "help";    // help keyword

    const char name = 'a';                  // t.kind = name of variable Token
    const char let = 'L';                   // t.kind = declaration token
    const std::string declkey = "let";      // declaration keyword
    const char constant = 'C';              // t.kind = constant declaration Token
    const std::string declkey_const = "const";// constant declaration keyword

    const char func = 'F';      // t.kind = function Token

    //------------------------------------------------------------------------------

    class Token
    {
    public:
        char kind;
        double value;
        std::string name;

        Token();
        Token(char ch, double val = 0.0);
        Token(char ch, std::string s);
        ~Token();
    };

    //------------------------------------------------------------------------------

    class Token_Stream
    {
    public:
        Token_Stream();
        Token_Stream(std::istream& /*tsin*/); // Token_stream that reads from an istream
        ~Token_Stream();

        Token get();
        void putback(const Token t);
        void ignore(const char c);

    private:
        bool full;      // is there a Token in the buffer?
        Token buffer;   // here is where we keep a Token put back using putback()
    };

}

#endif	// close header guard