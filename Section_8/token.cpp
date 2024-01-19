#include "token.hpp"
#include "../includes/ppp.hpp"
#include <iostream>

namespace calculator
{
    Token_Stream::Token_Stream( std::istream& tsin )
    {}

    Token Token_Stream::get()
    {
        if( full )  //check if we already have a Token ready
        {
            full = false;
            return buffer;
        }
        Token temp{ 0 };
        char ch{};
        // eat spaces and capture newline
        while( std::cin.get( ch ) &&
               ( std::isspace( static_cast<unsigned char>( ch ) ) || ch == newline ) )
        {
            if( ch == newline )
            {
                ch = print;
                break;
            }
        }
        switch( ch )
        {
            // tokens
            case print:
            case '(': case ')':
            case ',':                   // function argument separation
            case '+': case '-':
            case '*': case '/':
            case '%':
                temp = { ch };
                break;
            case '=':
                if( this->buffer.kind != let && this->buffer.kind != clet && this->buffer.kind != name )
                {
                    const std::string s =
                        ( this->buffer.kind == name ? this->buffer.name : std::to_string( this->buffer.value ) );
                    ppp::error( s, " can not be re-assigned" );
                }
                temp = { ch };
                break;

                // get floating point number
            case '.':
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                std::cin.putback( ch ); // put digit back into the input stream
                double val;
                std::cin >> val;        // read a floating-point number
                temp = { number, val };
                break;
            }
            default:
                if( std::isalpha( static_cast<unsigned char>( ch ) ) || ch == '_' )
                {
                    std::string s;
                    s += ch;
                    while( std::cin.get( ch ) &&
                           ( std::isalpha( static_cast<unsigned char>( ch ) ) || std::isdigit( static_cast<unsigned char>( ch ) ) || ch == '_' ) )
                    {
                        s += ch;
                    }
                    while( std::isspace( static_cast<unsigned char>( ch ) ) && ch != newline && std::cin.get( ch ) ) { /*eat spaces*/ }
                    std::cin.putback( ch );
                    if( s == declkey )
                    {
                        temp = { let };
                    }
                    else if( s == constdeclkey )
                    {
                        temp = { clet };
                    }
                    else if( ch == '(' )
                    {
                        temp = { func, s };
                    }
                    else if( s == declquit || s == std::string{ quit } )
                    {
                        temp = { quit };
                    }
                    else if( s == declhelp || s == std::string{ help } || s == "H" )
                    {
                        temp = { help };
                    }
                    else
                    {
                        temp = { name, s };
                    }
                }
                else
                {
                    ppp::error( "Bad token" );
                }
        }
        return temp;
    }

    // put a Token back
    void Token_Stream::putback( const Token t )
    {
        if( full )
        {
            ppp::error( "putback() into a full buffer" );
        }
        buffer = t;
        full = true;
    }

    // discard characters up to and including the given input kind token
    void Token_Stream::ignore( const char c )
    {
        if( full && c == buffer.kind )
        {
            full = false;
        }
        else
        {
            full = false;
            std::cin.clear();
            std::cin.ignore( std::cin.rdbuf()->in_avail(), c );
        }
    }

} // calculator
