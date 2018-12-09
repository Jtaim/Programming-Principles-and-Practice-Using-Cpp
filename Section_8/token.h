#ifndef TOKEN_H	// begin header guard
#define TOKEN_H

#include <string>

namespace calculator
{

    constexpr char number = '8';    // t.kind == number means that t is a number Token.
    constexpr char quit = 'q';      // t.kind == quit means that t is a quit Token.
    constexpr char print = ';';     // t.kind == print means that t is a print Token.

    constexpr char name = 'a';      // name token
    constexpr char let = 'L';       // declaration token
    constexpr char* declkey = "let"; // declaration keyword

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