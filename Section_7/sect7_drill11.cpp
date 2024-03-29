//Written by Jtaim
//Date 15 Dec 2018
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup
/*
	Section 7 Drill 7
	give the calculator a square root function
	Section 7 Drill 8
	check for negative numbers before using square root function and give an error
	Section 7 Drill 9
	give the calculator a power function pow(val, pow)

	Section 7 Drill 10
	change declaration keyword from let to #
	Section 7 Drill 11
	change declaration keyword quit to exit
*/

/*
    Calculate:
            prompt "print"              // termination of expression and print results
            prompt "quit"               // quit the program
            statement                   // continue to find an expression
    Statement:
            "let" Declaration           // define a named value
            Expression                  // continue to find an expression
    Declaration:
            Declaration name            // get name and check for duplication
            Declaration "=" Expression  // check assignment character
    Expression:
            Term
            Expression "+" Term         // addition
            Expression "�" Term         // subtraction
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
            Functions
    Number:
            floating-point-literal
*/

#include "../includes/ppp.hpp"

// program symbolic names
constexpr std::string_view prompt = "> ";       // indicate a prompt
constexpr std::string_view result = "= ";       // indicate a result
constexpr char number = '8';                    // t.kind == number means that t is a number Token.
constexpr char quit = 'q';                      // t.kind == quit means that t is a quit Token.
constexpr std::string_view quitkey = "exit";    // declaration quit
constexpr char print = ';';                     // t.kind == print means that t is a print Token.
constexpr char name = 'a';                      // name token
constexpr char let = 'L';                       // declaration token
constexpr char declkey = '#';                   // declaration keyword
constexpr char func = 'F';                      // function Token

struct Token
{
    char kind;
    double value;
    std::string name;

    //constructors
    Token( char ch ) : kind{ ch }, value{} {}
    Token( char ch, double val ) : kind{ ch }, value{ val } {}
    Token( char ch, std::string s ) : kind{ ch }, value{}, name{ s } {}
};

//------------------------------------------------------------------------------

// place to hold variable name value
struct Variable
{
    std::string name;
    double value{};
};

// overload equality operator to simplify get, set and is_declared functions 
bool operator==( const Variable& v, const std::string s )
{
    return v.name == s;
}

// container for all the variables
std::vector<Variable> names;

// return the value of the Variable with the input name.
double get_value( const std::string s )
{
    auto vt_itr = std::find( names.cbegin(), names.cend(), s );
    if( vt_itr == names.cend() )
    {
        ppp::error( "get: undefined name ", s );
    }
    return vt_itr->value;
}

// set the Variable of the named to a double value.
void set_value( const std::string s, const double d )
{
    auto vt_itr = std::find( names.begin(), names.end(), s );
    if( vt_itr == names.cend() )
    {
        ppp::error( "set: undefined name ", s );
    }
    vt_itr->value = d;
}

// is a name already declared
bool is_declared( const std::string s )
{
    return names.cend() != std::find( names.cbegin(), names.cend(), s );
}

// add name value to a vector of Variables
double define_name( const std::string s, const double d )
{
    if( is_declared( s ) )
    {
        ppp::error( s, " declared twice" );
    }
    names.push_back( Variable{ s, d } );
    return d;
}

//------------------------------------------------------------------------------

// place to hold valid Tokens from cin
class Token_stream
{
public:
    Token_stream() :full{ false }, buffer{ 0 } {}
    Token get();                    // get a Token to place in the stream
    void putback( const Token t );  // put a Token back
    void ignore( const char c );    // discard characters up to and including the given input kind token
private:
    bool full;                      // is there a Token in the buffer?
    Token buffer;                   // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if( full )  //check if we already have a Token ready
    {
        full = false;
        return buffer;
    }
    Token temp{ 0 };
    char ch{};
    std::cin >> ch;
    switch( ch )
    {
        // tokens
        case print:
        case quit:
        case '(': case ')':
        case ',':      // function argument separation
        case '+': case '-':
        case '*': case '/':
        case '%':
            temp = { ch };
            break;
        case '=':
            if( this->buffer.kind != let )
            {
                // should we let name values be reassigned? but what if const predefined names like pi or e?
                const std::string s = ( this->buffer.kind == name ? this->buffer.name : std::to_string( this->buffer.value ) );
                ppp::error( s, " can not be re-assigned" );
            }
            temp = { ch };
            break;

        case '.':      // get floating point number
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            std::cin.putback( ch ); // put digit back into the input stream
            double val;
            std::cin >> val;        // read a floating-point number
            temp = { number, val };
            break;
        }
        case declkey:   // declaration key
            temp = { let };
            break;
        default:
            if( isalpha( ch ) )
            {
                std::string s;
                s += ch;
                while( std::cin.get( ch ) && ( isalpha( static_cast<unsigned char>( ch ) ) || isdigit( static_cast<unsigned char>( ch ) ) ) )
                {
                    s += ch;
                }
                while( isblank( static_cast<unsigned char>( ch ) ) && std::cin.get( ch ) ) {} // eat spaces
                std::cin.putback( ch );
                if( s == quitkey )
                {
                    temp = { quit };
                }
                else if( ch == '(' )
                {
                    temp = { func, s };
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

void Token_stream::putback( const Token t )
{
    if( full )
    {
        ppp::error( "putback() into a full buffer" );
    }
    buffer = t;
    full = true;
}

void Token_stream::ignore( const char c )
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

Token_stream ts;

//------------------------------------------------------------------------------

double expression();
double function( const std::string& f );

//------------------------------------------------------------------------------

double primary()
{
    Token t = ts.get();
    double d{};
    switch( t.kind )
    {
        case '(':
        {
            d = expression();
            t = ts.get();
            if( t.kind != ')' )
            {
                ppp::error( "')' expected" );
            }
            break;
        }
        case '-':   // negative unary operator
            d = -1 * primary();
            break;
        case '+':   // positive unary operator
            d = primary();
            break;
        case number:
            d = t.value;
            break;
        case name:
            d = get_value( t.name );
            break;
        case func:
            d = function( t.name );
            break;
        default:
            ppp::error( "primary expected" );
    }
    return d;
}

//------------------------------------------------------------------------------

double term()
{
    double left = primary();
    while( true )
    {
        Token t = ts.get();
        switch( t.kind )
        {
            case '*':
                left *= primary();
                break;
            case '/':
            {
                double d = primary();
                if( d == 0 ) ppp::error( "divide by zero" );
                left /= d;
                break;
            }
            case '%':
            {
                double d = primary();
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

double expression()
{
    double left = term();
    while( true )
    {
        Token t = ts.get();
        switch( t.kind )
        {
            case '+':
                left += term();
                break;
            case '-':
                left -= term();
                break;
            default:
                ts.putback( t );
                return left;
        }
    }
}

//------------------------------------------------------------------------------

double declaration()
{
    Token t = ts.get();
    if( t.kind != name )
    {
        ppp::error( "name expected in declaration" );
    }
    if( is_declared( t.name ) )
    {
        ppp::error( t.name, " declared twice" );
    }
    Token t2 = ts.get();
    if( t2.kind != '=' )
    {
        ppp::error( "= missing in declaration of ", t.name );
    }
    double d = expression();
    define_name( t.name, d );
    return d;
}

//------------------------------------------------------------------------------

double function( const std::string& f )
{
    std::vector<double> func_args;
    double d{};
    Token t = ts.get();
    if( t.kind != '(' )
    {
        ppp::error( "'(' expected before function arguments" );
    }
    while( true )
    {
        func_args.push_back( expression() );
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
        d = func_args[0];
        if( func_args[0] < 0 )
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
        d = std::pow( func_args[0], func_args[1] );
    }
    else
    {
        ppp::error( "unknown function" );
    }
    return d;
}

//------------------------------------------------------------------------------

double statement()
{
    Token t = ts.get();
    switch( t.kind )
    {
        case let:
            return declaration();
        default:
            ts.putback( t );
            return expression();
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore( print );
}

//------------------------------------------------------------------------------

void calculate()
{
    while( true ) try
    {
        std::cout << prompt;
        Token t = ts.get();
        while( t.kind == print ) t = ts.get();
        if( t.kind == quit ) return;
        ts.putback( t );
        std::cout << result << statement() << std::endl;
    }
    catch( std::runtime_error& e )
    {
        std::cerr << e.what() << std::endl;
        clean_up_mess();
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
