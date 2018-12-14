#include "token.h"
#include <iostream>

calculator::Token::Token()
    : kind('\0'), value(0.0), name("")
{
}

calculator::Token::Token(char ch, double val)
    : kind(ch), value(val), name("")
{
}

calculator::Token::Token(char ch, std::string s)
    : kind(ch), value(0.0), name(s)
{
}

calculator::Token::~Token()
{
}

//------------------------------------------------------------------------------

calculator::Token_Stream::Token_Stream()
    : full(false), buffer('\0')
{
    // un-sync C++ stream from c streams
    std::cin.sync_with_stdio(false);
}

calculator::Token_Stream::Token_Stream(std::istream& /*tsin*/)
    : full(false), buffer('\0')
{
}

calculator::Token_Stream::~Token_Stream()
{
    // redo-sync C++ stream from c streams
    std::cin.sync_with_stdio(true);
}

/// get a Token to place in the stream
calculator::Token calculator::Token_Stream::get()
{
    Token token{};
    if (full) {
        full = false;
        token = buffer;
    }
    else {
        char ch;
        std::cin >> ch;
        switch (ch) {
        case print:
        case quit:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
            //case '%':
            token.kind = ch;
            break;
        case '=':
            if (this->buffer.kind != let) throw std::runtime_error("Assignment Denied");
            token.kind = ch;
            break;
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            std::cin.putback(ch);
            double val;
            std::cin >> val;
            token.kind = number;
            token.value = val;
        }
        break;
        default:
            if (isalpha(ch)) {
                std::string s;
                s += ch;
                while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) {
                    s += ch;
                }
                std::cin.putback(ch);
                if (s == declkey) {
                    token.kind = let;
                    break;
                }
                if (s == "quit") {
                    // TODO handle if found string "quit" 
                }
                token.kind = name;
                token.name = s;
            }
            else {
                throw std::runtime_error("Bad token");
            }
        }
    }
    return token;
}

/// put a Token back
void calculator::Token_Stream::putback(const Token t)
{
    if (full) {
        throw std::runtime_error("putback() into a full buffer");
    }
    buffer = t;
    full = true;
}

/// discard characters up to and including the given input kind token
void calculator::Token_Stream::ignore(const char c)
{
    if (full && c == buffer.kind) {
        full = false;
    }
    else {
        full = false;
        std::cin.clear();
        // check if buffer is empty
        auto cb = std::cin.rdbuf()->in_avail();
        while (cb) {
            char trash{};
            std::cin.get(trash);    //clear buffer
            if (c == trash) break;
            --cb;
        }
    }
}
