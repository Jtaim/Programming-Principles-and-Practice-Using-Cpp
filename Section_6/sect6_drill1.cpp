
//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
  This file is known as calculator02buggy.cpp but now fixed and renamed to sect6_drill1.cpp

  I have inserted 5 errors that should cause this not to compile
  I have inserted 3 logic errors that should cause the program to give wrong results

  First try to find an remove the bugs without looking in the book.
  If that gets tedious, compare the code to that in the book (or posted source code)

  Happy hunting!

  think fixed errors but found if enter example 3+2 6 2+5;
  program will eat 3+2 and 6 but give answer to 2+5
*/

#include "section6.h"

class Token
{
public:
    char kind;		// what kind of token
    double value;   // for numbers: a value 

    //constructor
    Token( char ch, double val = 0 ) : kind{ ch }, value{ val } {}
};

//------------------------------------------------------------------------------

class Token_stream
{
public:
    // The constructor just sets full to indicate that the buffer is empty:
    Token_stream() : full{ false }, buffer{ 0 } {}
    Token get();				// get a Token (get() is defined elsewhere)
    void putback( Token t );    // put a Token back
private:
    bool full;      			// is there a Token in the buffer?
    Token buffer;				// here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback( Token t )
{
    if( full )
    {
        error( "putback() into a full buffer" );
    }
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{

    // do we already have a Token ready?
    if( full )
    {
        full = false;
        return buffer;
    }
    Token temp{ 0 };
    char ch;
    std::cin >> ch;
    switch( ch )
    {
        case ';':				    // for "print"
        case 'q':				    // for "quit"
        case '(': case ')': case '*': case '/': case '+': case '-':
            temp = { ch };
            break;
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            std::cin.putback( ch ); // put digit back into the input stream
            double val;
            std::cin >> val;		// read a floating-point number
            temp = { '8', val };
            break;
        }
        default:
            error( "Bad token" );
    }
    return temp;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------
// deal with numbers and parentheses
double primary()
{
    double temp{};                  // temp storage for the returns
    Token t = ts.get();

    switch( t.kind )
    {
        case '(':			        // handle '(' expression ')'
        {
            temp = expression();
            t = ts.get();
            if( t.kind != ')' )
            {
                error( "')' expected" );
            }
            break;
        }
        case '-':                   // deal with - unary operator
            temp = -1 * primary();
            break;
        case '+':			        // deal with + unary operator
            temp = primary();
            break;
        case '8':			        // we use '8' to represent a number
            temp = t.value;	        // return the number's value
            break;
        default:
            error( "primary expected" );
    }
    return temp;
}

//------------------------------------------------------------------------------

// deal with * and /
// % not implemented yet
double term()
{
    double left = primary();
    Token t = ts.get();             // get the next token from token stream

    while( true )
    {
        switch( t.kind )
        {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if( d == 0 )
                {
                    error( "divide by zero" );
                }
                left /= d;
                t = ts.get();
                break;
            }
            default:
                ts.putback( t );    // put t back into the token stream
                return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();           // read and evaluate a Term
    Token t = ts.get();             // get the next token from token stream
    while( true )
    {
        switch( t.kind )
        {
            case '+':
                left += term();		// evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term();		// evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback( t );    // put t back into the token stream
                return left;		// finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

int main()
{
    try
    {
        double val{};
        while( std::cin )
        {
            Token t = ts.get();
            if( t.kind == 'q' ) // 'q' for quit
            {
                break;
            }
            if( t.kind == ';' ) // ';' for "print now"
            {
                std::cout << std::format( "= {}\n", val );
            }
            else
            {
                ts.putback( t );
                val = expression();
            }
        }
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
    keep_window_open();
    return 0;
}
