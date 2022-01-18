/*
    Written by Jtaim
    Sept 9, 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

    Add a command from x to the calculator from Chapter 7 that makes it take input from a file x.
    Add a command to y to the calculator that makes it write its output (both standard output and error output) to file y.
    Write a collection of test cases based on ideas from section 7.3 and use that to test the calculator.
    Discuss how you would use these commands for testing.
 */

#include "../includes/ppp.h"

 //------------------------------------------------------------------------------

constexpr char number = '8';    // t.kind == number means that t is a number Token.
constexpr char quit = 'q';      // t.kind == quit means that t is a quit Token.
constexpr std::string_view declexit = "exit";
constexpr char print = ';';     // t.kind == print means that t is a print Token.

constexpr char name = 'a';      // name token
constexpr char let = 'L';       // declaration token
constexpr std::string_view declkey = "let"; // declaration keyword
constexpr char func = 'F';      // function Token

constexpr char debug = 'D';		// Added file input and output
constexpr std::string_view declDebugIn = "from";	// declaration keyword for input debug file
constexpr std::string_view declDebugOut = "to";		// declaration keyword for output debug file

// global file declarations
std::ifstream fin;
std::ofstream fout;
std::streambuf *cinbuffer{nullptr};

class Token
{
public:
    Token(char ch, double val = 0.0) :kind{ch}, value{val}, name{} {}
    Token(char ch, std::string s) :kind{ch}, value{}, name{s} {}
    Token() : kind{}, value{}, name{} {}

    char kind;
    double value;
    std::string name;
};

//------------------------------------------------------------------------------

// place to hold variable name value
class Variable
{
public:
    //explicit Variable(std::string s, double v = 0) : name{s}, value{v} {}
    std::string name;
    double value;
};

// overload equality operator to simplify get, set and is_declared functions 
bool operator==(const Variable &v, const std::string s)
{
    return v.name == s;
}
bool operator==(const std::string s, const Variable &v)
{
    return s == v.name;
}

// TODO working with name value pair can be simplified by using a std::map container
std::vector<Variable> var_table;

// return the value of the Variable with the input name.
double get_value(const std::string s)
{
    auto vt{std::find(var_table.begin(), var_table.end(), s)};
    if(vt == var_table.end()) {
        ppp::error("get: undefined variable " + s);
    }
    return vt->value;
}

// set the Variable of the named to a double value.
void set_value(const std::string s, const double d)
{
    auto vt{std::find(var_table.begin(), var_table.end(), s)};
    if(vt == var_table.end()) {
        ppp::error("set: undefined variable " + s);
    }
    vt->value = d;
}

// is a name already declared
bool is_declared(const std::string s)
{
    auto vt{std::find(var_table.begin(), var_table.end(), s)};
    return vt != var_table.end();
}

// add name value to a vector of Variables
double define_name(const std::string s, const double d)
{
    if(is_declared(s)) {
        ppp::error(s + " declared twice");
    }
    var_table.push_back(Variable{s, d});
    return d;
}

//------------------------------------------------------------------------------

class Token_stream
{
public:
    // The constructor just sets full to indicate that the buffer is empty:
    Token_stream()					// make a Token_stream that reads from cin
        :full{false}, buffer{} {}	// no Token in buffer
    Token get();					// get a Token to place in the stream
    void putback(const Token t);    // put a Token back
    void ignore(const char c);      // discard characters up to and including the given input kind token
private:
    bool full;      				// is there a Token in the buffer?
    Token buffer;					// here is where we keep a Token put back using putback()
};

void Token_stream::ignore(const char c)
{
    // first look in buffer.
    if(full && c == buffer.kind) {
        full = false;
    } else {
        full = false;
        std::cin.clear();
        if(fout.is_open()) {
            fout << "ignoring: ";
        }
        for(char ch{}; std::cin >> ch;) {
            if(fout.is_open()) {
                fout << ch;
            }
            if(ch == c) {
                fout << "\n";
                break;
            }
        }
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), c);
    }
}

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if(full) {
        ppp::error("putback() into a full buffer");
    }
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

Token Token_stream::get()
{
    Token temp;

    // do we already have a Token ready?
    if(full) {
        full = false;
        temp = buffer;
    } else {
        char ch{};
        std::cin >> ch;
        if(fout.is_open()) {
            fout << "get() char: " << ch << "\n";
        }
        switch(ch) {
            case print:
            case quit:
            case '(': case ')':
            case '*':
            case '/':
            case '%':
            case '+':
            case '-':
            case '!':
            case ',':
            case '=':
                temp.kind = ch;
                break;
            case '.':
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                std::cin.putback(ch);	// put digit back into the input stream
                double val{};
                std::cin >> val;		// read a floating-point number
                if(fout.is_open()) {
                    fout << "get() number: " << val << "\n";
                }
                temp = Token{number, val};
                break;
            }
            default:
                if(std::isalpha(static_cast<unsigned char>(ch)) || ch == '_') {
                    std::string s;
                    s += ch;
                    while(std::cin.get(ch) &&
                        (std::isalpha(static_cast<unsigned char>(ch)) ||
                         std::isdigit(static_cast<unsigned char>(ch)) ||
                         ch == '_')) {
                        s += ch;
                    }
                    if(fout.is_open()) {
                        fout << "get() string: " << s << "\n";
                    }
                    std::cin.putback(ch);
                    if(s == declkey) {
                        temp.kind = let;
                    } else if(s == declDebugIn) {
                        temp.kind = debug;
                        temp.name = s;
                    } else if(s == declDebugOut) {
                        temp.kind = debug;
                        temp.name = s;
                    } else if(ch == '(') {
                        temp.kind = func;
                        temp.name = s;
                    } else if(s == declexit) {
                        temp.kind = quit;
                    } else {
                        temp.kind = name;
                        temp.name = s;
                    }
                } else {
                    ppp::error("Bad token");
                }
        }
    }
    return temp;
}
Token_stream ts;    // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();            // declaration so that primary() can call expression()
long long fact(long long val);  // forward declaration
double function(const std::string &s);

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t{ts.get()};
    double temp{};  // temp storage for the returns
    switch(t.kind) {
        case '(':			// handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if(t.kind != ')') {
                ppp::error("')' expected");
            }
            temp = d;
            break;
        }
        case '-': case '+': // deal with +/- unary operators
        {
            auto unary = t.kind;
            t = ts.get();
            if(t.kind == number) {
                unary == '-' ? t.value *= -1 : t.value;
            } else if(t.kind == '!') {
                t.value = 1;
            } else {
                ppp::error("primary expected");
            }
        }
        [[fallthrough]] ;
        case number:
            temp = t.value;	// return the number's value
            t = ts.get();
            // check if followed by factorial
            if(t.kind == '!') {
                temp = ppp::narrow_cast<double, long long>(fact(ppp::narrow_cast<long long, double>(temp)));
            } else {
                ts.putback(t);
            }
            break;
        case '!':   // deal with ! without preceding number assume is 1
            temp = 1;
            break;
        case name:
            temp = get_value(t.name);
            break;
        case func:
            temp = function(t.name);
            break;
        default:
            std::cin.putback(t.kind);
            ppp::error("primary expected");
    }
    return temp;
}

//------------------------------------------------------------------------------

// deal with * / and %
double term()
{
    double left{primary()};
    while(true) {
        Token t{ts.get()};
        switch(t.kind) {
            case '*':
                left *= primary();
                break;
            case '/':
            {
                double d{primary()};
                if(d == 0) {
                    ppp::error("divide by zero");
                }
                left /= d;
                break;
            }
            case '%':
            {
                double d{primary()};
                if(d == 0) {
                    ppp::error("divide by zero");
                }
                left = fmod(left, d);
                break;
            }
            default:
                ts.putback(t);		// put t back into the token stream
                return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left{term()};		// read and evaluate a Term
    while(true) {
        Token t{ts.get()};
        switch(t.kind) {
            case '+':
                left += term();		// evaluate Term and add
                break;
            case '-':
                left -= term();		// evaluate Term and subtract
                break;
            case ',':   // let fall through
            default:
                ts.putback(t);		// put t back into the token stream
                return left;		// finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

/* assume we have seen let.
   handle: name=expression.
   declare a variable called "name" with the initial value "expression". */
double declaration()
{
    Token t{ts.get()};
    if(t.kind != name) {
        ppp::error("name expected in declaration");
    }

    if(is_declared(t.name)) {
        ppp::error(t.name + " declared twice");
    }

    Token t2{ts.get()};
    if(t2.kind != '=') {
        ppp::error("= missing in declaration of " + t.name);
    }
    double d{expression()};
    define_name(t.name, d);
    return d;
}

//------------------------------------------------------------------------------

double func_availible(const std::string &s, const std::vector<double> &args)
{
    double d{};
    if(s == "sqrt") {
        if(args.size() != 1) {
            ppp::error("sqrt() expects 1 argument");
        }
        if(args.at(0) < 0) {
            ppp::error("sqrt() expects argument value >= 0");
        }
        d = sqrt(args.at(0));
    } else if(s == "pow") {
        if(args.size() != 2) {
            ppp::error("pow() expects 2 arguments");
        }
        d = args.at(0);
        auto multiplier{args.at(0)};
        auto p{ppp::narrow_cast<int>(args.at(1))};
        for(; p > 1; --p) {
            d *= multiplier;
        }
    } else {
        ppp::error("unknown function");
    }
    return d;
}

//------------------------------------------------------------------------------

double function(const std::string &s)
{
    Token t{ts.get()};
    std::vector<double> func_args;
    if(t.kind != '(') {
        ppp::error("expected '(', malformed function call");
    } else {
        do {
            t = ts.get();
            // true check for arguments
            // false if no arguments
            if(t.kind != ')') {
                ts.putback(t);
                func_args.push_back(expression());
                t = ts.get();
                if(t.kind != ',' && t.kind != ')') {
                    ppp::error("expected ')', malformed function call");
                }
            }
        } while(t.kind != ')');
    }
    return func_availible(s, func_args);
}

//------------------------------------------------------------------------------

double statement()
{
    Token t{ts.get()};
    double d{};
    switch(t.kind) {
        case let:
            d = declaration();
            break;
        case name:
        {
            Token t2{ts.get()};
            if(t2.kind != '=') {
                std::cin.putback(t2.kind);
                ts.putback(t);
                d = expression();
            } else {
                d = expression();
                set_value(t.name, d);
            }
            break;
        }
        default:
            ts.putback(t);
            d = expression();
    }
    return d;
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate()        // expression evaluation loop
{
    constexpr std::string_view prompt = "> ";  // indicate a prompt
    constexpr std::string_view result = "= ";  // indicate a result

    while(true)
        try {
        std::cout << prompt;
        if(fout.is_open()) {
            fout << prompt;
        }
        Token t{ts.get()};
        while(t.kind == print) {
            t = ts.get();   // eat print   
        }
        if(t.kind == quit) {
            std::cout << "Bye\n";
            break;
        } else if(t.kind == debug && t.name == declDebugIn) {

            std::string file_name{"sect10_ex10_input.txt"};
            //std::cin >> filename;
            fin.open(file_name);
            if(!fin) {
                ppp::error("Could not find debug input file ", file_name);
            }
            cinbuffer = std::cin.rdbuf();
            std::cin.rdbuf(fin.rdbuf());
            continue;
        } else if(t.kind == debug && t.name == declDebugOut) {

            std::string file_name{"sect10_ex10_output.txt"};
            //std::cin >> filename;
            fout.open(file_name);
            if(!fout) {
                ppp::error("Could not find debug input file ", file_name);
            }
            continue;
        }
        ts.putback(t);
        auto res{statement()};
        std::cout << result << res << '\n';
        if(fout.is_open()) {
            fout << result << res << '\n';
        }
    }
    catch(std::exception &e) {
        std::cerr << e.what() << '\n';
        if(fout.is_open()) {
            fout << "ERROR: " << e.what() << '\n';
        }
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

int main()
try {
    std::cout << "\nWelcome to our simple calculator.\n"
        << "Please enter expressions using floating-point numbers.\n"
        << "Operations available are +, -, *, /, % and n!.\n"
        << "Can change order of operations using ( ).\n"
        << "Can use type name variables."
        << "Use the '" << print << "' to show results and '" << quit << "' to quit.\n\n"
        << "Just type \"to\" then \"from\". I hard coded the text files.\n\n";


    // predefined names:
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);

    calculate();

    std::cin.rdbuf(cinbuffer);
    ppp::keep_window_open();
    return 0;
}
catch(std::exception &e) {
    std::cerr << "error: " << e.what() << '\n';
    ppp::keep_window_open();
    return 1;
}
catch(...) {
    std::cerr << "Oops: unknown exception!\n";
    ppp::keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------

// real number factorial.  Floating point factorial gets scary, have to use gamma function?
long long fact(long long val)
{
    if(val < 0) {
        val = abs(val);
    } else if(val == 0) {
        val = 1;
    }

    decltype(val) n = 1;
    for(long long i{1}; i <= val; ++i) {
        n *= i;
        // no overflow check
    }
    return n;
}
