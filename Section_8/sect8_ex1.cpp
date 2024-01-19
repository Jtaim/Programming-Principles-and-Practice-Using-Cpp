/*
    Written by Jtaim
    Date 8 Dec 2018
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup
    Section 8 Exercise 1
*/

// Modify the calculator program from Chapter 7 to make the input stream an explicit parameter (as shown in section 8.5.8),
// rather than simply using cin. 
// Also give the Token_stream constructor (section 7.8.2) an istream& parameter so that when we figure out how to make our own istreams
// (e.g., attached to files),
// we can use the calculator for those. 
// Hint: Don’t try to copy an istream.

/*
    Calculate:
            prompt: ';', '/n'           // termination of expression and print results
            prompt: 'q', "quit"         // quit the program
            help: 'h', 'H', "help"      // help about the calculator
            statement                   // continue to find an expression
    Statement:
            "let" Declaration           // define a named value
            "const" Declaration         // define a constant vale
            Expression                  // continue to find an expression
    Declaration:
            Declaration name            // get name and check for duplication
            Declaration "=" Expression  // check assignment character
    Expression:
            Term
            Expression "+" Term         // addition
            Expression "–" Term         // subtraction
    Term:
            Primary
            Term "*" Primary            // multiplication
            Term "/" Primary            // division
            Term "%" Primary            // remainder (modulo)
    Primary:
            Number
            "(" Expression ")"          // grouping
            "+" Primary                 // positive unary operator
            "-" Primary                 // negative unary operator
            Name_Value                  // named value
            Functions(Expression , ...)
    Number:
            floating-point-literal
*/

#include "../includes/ppp.hpp"
#include "token.hpp"
#include "symbol_table.hpp"

using namespace calculator;

// program symbolic names
constexpr std::string_view prompt = "> ";           // indicate a prompt
constexpr std::string_view result = "= ";           // indicate a result

// help information
const std::string calculator_help{
    std::format( "Welcome to our simple calculator.\n"
                 "Please enter expressions using floating-point numbers.\n"
                 "Operations available are +, -, *, /, %.\n"
                 "Can change order of operations using ( ).\n"
                 "Can use name variables. Use a prefix of {0} to declare a named variable\n"
                 "Can use const name variables. Use a prefix of {1} to declare a const named variable\n"
                 "Non const named variables can be reassigned.\n"
                 "functions available are pow(arg, p) and sqrt(arg).\n"
                 "Use the '{2}' or enter key to show results.\n"
                 "'{3}' or \"quit\" to quit.\n\n",
                 declkey, constdeclkey, print, quit ) };

//------------------------------------------------------------------------------

double expression( Token_Stream& ts );
double function( Token_Stream& ts, const std::string& s );

//------------------------------------------------------------------------------

double primary( Token_Stream& ts )
{
    Token t = ts.get();
    double d{};
    switch( t.kind )
    {
        case '(':
        {
            d = expression( ts );
            t = ts.get();
            if( t.kind != ')' )
            {
                ppp::error( "')' expected" );
            }
            break;
        }
        case '-':   // negative unary operator
            d = -1 * primary( ts );
            break;
        case '+':   // positive unary operator
            d = primary( ts );
            break;
        case number:
            d = t.value;
            break;
        case name:
        {
            const std::string temp = t.name;
            t = ts.get();
            if( t.kind == '=' )
            {
                d = expression( ts );
                ts.symbol_table.set_value( temp, d );
            }
            else
            {
                ts.putback( t );
                d = ts.symbol_table.get_value( temp );
            }
        }
        break;
        case func:
            d = function( ts, t.name );
            break;
        default:
            ppp::error( "primary expected" );
    }
    return d;
}

//------------------------------------------------------------------------------

double term( Token_Stream& ts )
{
    double left = primary( ts );
    while( true )
    {
        Token t = ts.get();
        switch( t.kind )
        {
            case '*':
                left *= primary( ts );
                break;
            case '/':
            {
                double d = primary( ts );
                if( d == 0 ) ppp::error( "divide by zero" );
                left /= d;
                break;
            }
            case '%':
            {
                double d = primary( ts );
                if( d == 0 )
                {
                    ppp::error( "divide by zero" );
                }
                left = std::fmod( left, d );
                break;
            }
            default:
                ts.putback( t );
                return left;
        }
    }
}

//------------------------------------------------------------------------------

double expression( Token_Stream& ts )
{
    double left = term( ts );
    while( true )
    {
        Token t = ts.get();
        switch( t.kind )
        {
            case '+':
                left += term( ts );
                break;
            case '-':
                left -= term( ts );
                break;
            default:
                ts.putback( t );
                return left;
        }
    }
}

//------------------------------------------------------------------------------

double declaration( Token_Stream& ts, bool c = false )
{
    Token t = ts.get();
    if( t.kind != name )
    {
        ppp::error( "name expected in declaration" );
    }
    if( ts.symbol_table.is_declared( t.name ) )
    {
        ppp::error( t.name, " declared twice" );
    }
    Token t2 = ts.get();
    if( t2.kind != '=' )
    {
        ppp::error( "= missing in declaration of ", t.name );
    }
    double d = expression( ts );
    ts.symbol_table.declare( t.name, d, c );
    return d;
}

//------------------------------------------------------------------------------

double function( Token_Stream& ts, const std::string& f )
{
    std::vector<double> func_args;
    double d{};
    Token t = ts.get();
    if( t.kind != '(' )
    {
        ppp::error( "'(' expected before function arguments" );
    }
    while( true )   // get function arguments
    {
        func_args.push_back( expression( ts ) );
        t = ts.get();
        if( t.kind == ')' ) break;
        else if( t.kind != ',' )
        {
            ppp::error( "expected ')', malformed function call" );
        }
    }

    if( f == "sqrt" )
    {
        if( func_args.size() != 1 )
        {
            ppp::error( "sqrt() expects 1 argument" );
        }
        d = func_args.at( 0 );
        if( d < 0 )
        {
            ppp::error( "sqrt() expects argument value >= 0" );
        }
        d = std::sqrt( d );
    }
    else if( f == "pow" )
    {
        if( func_args.size() != 2 )
        {
            ppp::error( "pow() expects 2 arguments" );
        }
        d = std::pow( func_args.at( 0 ), func_args.at( 1 ) );
    }
    else
    {
        ppp::error( "unknown function" );
    }
    return d;
}

//------------------------------------------------------------------------------

double statement( Token_Stream& ts )
{
    Token t = ts.get();
    switch( t.kind )
    {
        case let:
            return declaration( ts );
        case clet:
            return declaration( ts, true );
        default:
            ts.putback( t );
            return expression( ts );
    }
}

//------------------------------------------------------------------------------

void clean_up_mess( Token_Stream& ts )
{
    ts.ignore( print );
}

//------------------------------------------------------------------------------

void calculate()
{
    Token_Stream ts;
    ts.symbol_table.declare( "pi", std::numbers::pi, true );

    while( true ) try
    {
        std::cout << prompt;
        Token t = ts.get();
        while( t.kind == print )
        {
            t = ts.get();
        }
        if( t.kind == quit )
        {
            return;
        }
        else if( t.kind == help )
        {
            std::cout << calculator_help;
            continue;
        }
        ts.putback( t );
        std::cout << result << statement( ts ) << std::endl;
    }
    catch( std::runtime_error& e )
    {
        std::cerr << e.what() << std::endl;
        clean_up_mess( ts );
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    calculate();
    return 0;
}
catch( std::exception& e )
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
