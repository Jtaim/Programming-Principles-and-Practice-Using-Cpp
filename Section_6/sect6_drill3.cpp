/*
  written by Jtaim
  date 12 Nov 2018
  Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

  Section 6 Drill 3
  Replace ; with = to indicate end of expression
*/

#include "section6.h"

constexpr char quit = 'x';
constexpr char print = '=';

class Token
{
public:
    char kind;		// what kind of token
    double value;	// for numbers: a value

    // constructors
    Token( char ch, double val = 0.0 ) : kind{ ch }, value{ val } {}
};

//------------------------------------------------------------------------------

class Token_stream
{
public:
    // The constructor just sets full to indicate that the buffer is empty:
    Token_stream() : full{ false }, buffer{ 0 } {}
    Token get();                // get a Token (get() is defined elsewhere)
    void putback( Token t );    // put a Token back
private:
    bool full;                  // is there a Token in the buffer?
    Token buffer;               // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback( Token t )
{
    // precondition check
    if( full )
    {
        error( "putback() into full buffer" );
    }
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    // do we already have a Token ready
    if( full )
    {
        // remove token from buffer
        full = false;
        return buffer;
    }
    char ch;
    std::cin >> ch;  // note that >> skips whitespace (space, newline, tab, etc.)

    Token temp{ 0 };
    switch( ch )
    {
        case print:                 // for "print"
        case quit:                  // for "quit"
        case '(': case ')': case '+': case '-': case '*': case '/':
            temp = { ch };          // let each character represent itself
            break;
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            std::cin.putback( ch ); // put digit back into the input stream
            double val;
            std::cin >> val;        // read a floating-point number
            temp = { '8', val };    // let '8' represent "a number"
        }
        break;
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
            double d = expression();
            t = ts.get();
            if( t.kind != ')' )
            {
                error( "')' expected" );
            }
            temp = d;
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
    Token t = ts.get(); // get the next token from token stream

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
                ts.putback( t );	// put t back into the token stream
                return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();           // read and evaluate a Term
    Token t = ts.get();		        // get the next token from token stream
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
            if( t.kind == quit )
            {
                break;
            }
            if( t.kind == print )
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

