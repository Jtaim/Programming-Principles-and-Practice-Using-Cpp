//Written by Jtaim
//Date 15 Dec 2018
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
    copied from drill 11 removed drill 10 stuff
    also added modulo
    section 7 exercise 1
    allow underscores in the calculator's variable names

    section 7 exercise 2
    modified how function is handled.  place call in primary and removed recursive call from function handler
    provide assignment operator = so can reassign already declared variables with let.
    The issue with this is to make sure there is no proceeding expression.
    example:
    let x = 2; x + 3; x = 4; //is ok
    x = 5 + x; //is ok were existing value of x added to 5 then new value into x
    x + 4 - x = 5; is not ok
    let y = 3; x = y = 5; is not ok ?

    section 7 exercise 3
    Provide named constants that you can't change the value of

    section 7 exercise 4
    Define a symbol table class

    section 7 exercise 5
    Modify Token_stream::get() to return Token(print) when it sees a newline.

    section 7 exercise 6
    Add print help instruction when see Token h or H only if it is first entry

    section 7 exercise 7
    removed exercise 6 functionality
    change the q and h commands to be "quit" and "help", respectively.
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
            Functions
    Number:
            floating-point-literal
*/

#include "../includes/ppp.hpp"

// program symbolic names
constexpr std::string_view prompt = "> ";           // indicate a prompt
constexpr std::string_view result = "= ";           // indicate a result
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

class Symbol_Table
{
public:
    double get_value( const std::string_view s );
    void set_value( const std::string_view s, const double d );
    bool is_declared( const std::string_view s );
    double declare( const std::string_view s, const double d, const bool set_const = false );

    Symbol_Table() = default;
    Symbol_Table( const Symbol_Table& st ) = delete;        // delete copy constructor    
    Symbol_Table( const Symbol_Table&& st ) = delete;       // delete move constructor
    Symbol_Table& operator=( Symbol_Table& st ) = delete;   // delete copy assignment operator
    Symbol_Table& operator=( Symbol_Table&& st ) = delete;  // delete move assignment operator
private:
    // place to hold variable name value
    struct Variable
    {
        std::string name;
        double value{};
        bool is_const{ false };
    };

    // container for all the variables
    std::vector<Variable> var_table;

    // private function to find name in var_table
    using vt_itr = std::vector<Variable>::iterator;
    vt_itr find_name( vt_itr first, vt_itr last, const std::string_view value )
    {
        for( ; first != last; ++first )
        {
            if( first->name == value )
            {
                return first;
            }
        }
        return last;
    }
};

// return the value of the Variable with the input name.
double Symbol_Table::get_value( const std::string_view s )
{
    auto vt = find_name( var_table.begin(), var_table.end(), s );
    if( vt == var_table.end() )
    {
        ppp::error( "get: undefined name ", s.data() );
    }
    return vt->value;
}

// set the Variable of the named to a double value.
void Symbol_Table::set_value( const std::string_view s, const double d )
{
    auto vt = find_name( var_table.begin(), var_table.end(), s );
    if( vt == var_table.end() )
    {
        ppp::error( "set: undefined name ", s.data() );
    }
    if( vt->is_const )
    {
        ppp::error( "set: is a constant" );
    }
    vt->value = d;
}

// is a name already declared
bool Symbol_Table::is_declared( const std::string_view s )
{
    auto vt = find_name( var_table.begin(), var_table.end(), s );
    return vt != var_table.end();
}

// add name value to a vector of Variables
double Symbol_Table::declare( const std::string_view s, const double d, const bool set_const )
{
    if( is_declared( s ) )
    {
        ppp::error( s.data(), " declared twice" );
    }
    var_table.push_back( Variable{ s.data(), d, set_const } );
    return d;
}

//------------------------------------------------------------------------------

Symbol_Table symbol_table;

//------------------------------------------------------------------------------

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

// place to hold valid Tokens from cin
class Token_stream
{
public:
    Token_stream() = default;
    Token get();                    // get a Token to place in the stream
    void putback( const Token t );  // put a Token back
    void ignore( const char c );    // discard characters up to and including the given input kind token
private:
    bool full{};                    // is there a Token in the buffer?
    Token buffer{ 0 };              // here is where we keep a Token put back using putback()
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
        {
            const std::string temp = t.name;
            t = ts.get();
            if( t.kind == '=' )
            {
                d = expression();
                symbol_table.set_value( temp, d );
            }
            else
            {
                ts.putback( t );
                d = symbol_table.get_value( temp );
            }
        }
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

double declaration( bool c = false )
{
    Token t = ts.get();
    if( t.kind != name )
    {
        ppp::error( "name expected in declaration" );
    }
    if( symbol_table.is_declared( t.name ) )
    {
        ppp::error( t.name, " declared twice" );
    }
    Token t2 = ts.get();
    if( t2.kind != '=' )
    {
        ppp::error( "= missing in declaration of ", t.name );
    }
    double d = expression();
    symbol_table.declare( t.name, d, c );
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
    while( true )   // get function arguments
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
        case clet:
            return declaration( true );
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
    symbol_table.declare( "pi", std::numbers::pi, true );

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
