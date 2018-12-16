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

#include "../includes/ppp.h"

//------------------------------------------------------------------------------

constexpr char number = '8';    // t.kind == number means that t is a number Token.
constexpr char quit = 'q';      // t.kind == quit means that t is a quit Token.
constexpr char *declexit = "exit";
constexpr char print = ';';     // t.kind == print means that t is a print Token.

constexpr char name = 'a';      // name token
constexpr char let = 'L';       // declaration token
constexpr char *declkey = "#"; // declaration keyword
constexpr char func = 'F';  // function Token

struct Token {
    char kind;
    double value;
    std::string name;
    Token(char ch, double val = 0.0) :kind(ch), value(val) {}
    Token(char ch, std::string s) :kind(ch), value(0.0), name(s) {}
};

//------------------------------------------------------------------------------

// place to hold variable name value
struct Variable {
    std::string name;
    double value{};
};

// overload equality operator to simplify get, set and is_declared functions 
bool operator==(const Variable &v, const std::string s) { return v.name == s; }

// container for all the variables
std::vector<Variable> names;

// return the value of the Variable with the input name.
double get_value(const std::string s)
{
    auto vt_itr = std::find(names.cbegin(), names.cend(), s);
    if (vt_itr == names.cend()) {
        throw std::runtime_error("get: undefined name " + s);
    }
    return vt_itr->value;
}

// set the Variable of the named to a double value.
void set_value(const std::string s, const double d)
{
    auto vt_itr = std::find(names.begin(), names.end(), s);
    if (vt_itr == names.cend()) {
        throw std::runtime_error("set: undefined name " + s);
    }
    vt_itr->value = d;
}

// is a name already declared
bool is_declared(const std::string s)
{
    return names.cend() != std::find(names.cbegin(), names.cend(), s);
}

// add name value to a vector of Variables
double define_name(const std::string s, const double d)
{
    if (is_declared(s)) throw std::runtime_error(s + " declared twice");
    names.push_back(Variable{ s, d });
    return d;
}

//------------------------------------------------------------------------------

// place to hold valid Tokens from cin
class Token_stream {
public:
    Token_stream() :full(false), buffer('\0') { }

    // get a Token to place in the stream
    Token get();

    // put a Token back
    void putback(const Token t);

    // discard characters up to and including the given input kind token
    void ignore(const char c);

private:
    bool full;      // is there a Token in the buffer?
    Token buffer;   // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    Token t{ '\0' };
    if (full) {
        full = false;
        t = buffer;
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
        case ',':
            //case '%':
            t.kind = ch;
            break;
        case '=':
            if (this->buffer.kind != let) {
                const std::string s = (this->buffer.kind == name ? this->buffer.name : std::to_string(this->buffer.value));
                throw std::runtime_error(s + " can not be re-assigned");
            }
            t.kind = ch;
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
            t.kind = number;
            t.value = val;
            break;
        }
        default:
            if (isalpha(ch)||(strlen(declkey)==1)) {
                std::string s;
                s += ch;
                if (ch != declkey[0]) {
                    while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
                    std::cin.putback(ch);
                }
                if (s == declkey) {
                    t.kind = let;
                }
                else if (ch == '(') {
                    t.kind = func;
                    t.name = s;
                }
                else if (s == declexit) {
                    t.kind = quit;
                }
                else {
                    t.kind = name;
                    t.name = s;
                }
            }
            else {
                throw std::runtime_error("Bad token");
            }
        }
    }
    return t;
}

void Token_stream::putback(const Token t)
{
    if (full) {
        throw std::runtime_error("putback() into a full buffer");
    }
    buffer = t;
    full = true;
}

void Token_stream::ignore(const char c)
{
    if (full && c == buffer.kind) {
        full = false;
    }
    else {
        full = false;
        ppp::clear_cin_buffer(c);
    }
}

Token_stream ts;

//------------------------------------------------------------------------------

double expression();

//------------------------------------------------------------------------------

double primary()
{
    Token t = ts.get();
    double d{};
    switch (t.kind) {
    case '(': {
        d = expression();
        t = ts.get();
        if (t.kind != ')') {
            throw std::runtime_error("')' expected");
        }
        return d;
    }
    case '-':
        return -1 * primary();
    case '+':
        return primary();
    case number:
        return t.value;
    case name:
        return get_value(t.name);
    default:
        throw std::runtime_error("primary expected");
    }
}

//------------------------------------------------------------------------------

double term()
{
    double left = primary();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
        case '*':
            left *= primary();
            break;
        case '/':
        {	double d = primary();
        if (d == 0) throw std::runtime_error("divide by zero");
        left /= d;
        break;
        }
        //case '%':
            // not implemented yet
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double expression()
{
    double left = term();
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double declaration()
{
    Token t = ts.get();
    if (t.kind != name) {
        throw std::runtime_error("name expected in declaration");
    }
    if (is_declared(t.name)) {
        throw std::runtime_error(t.name + " declared twice");
    }
    Token t2 = ts.get();
    if (t2.kind != '=') {
        throw std::runtime_error("= missing in declaration of " + t.name);
    }
    double d = expression();
    define_name(t.name, d);
    return d;
}

//------------------------------------------------------------------------------

double function(const std::string &s)
{
    Token t = ts.get();
    double d{};
    std::vector<double> func_args;
    if (t.kind != '(') {
        throw std::runtime_error("expected '(', malformed function call");
    }
    else {
        do {
            t = ts.get();
            // see if any argument is a function call
            if (t.kind == func) {
                t.kind = number;
                // recursive call
                t.value = function(t.name);
                ts.putback(t);
            }
            // check if empty arguments
            if(t.kind == ')'){
                break;
            }
            else {
                ts.putback(t);
            }
            // push valid function argument
            func_args.push_back(expression());
            t = ts.get();
            if (t.kind == ')') break;
            if (t.kind != ',') throw std::runtime_error("expected ')', malformed function call");
        } while (t.kind == ',');
    }

    if (s == "sqrt") {
        if (func_args.size() != 1) throw std::runtime_error("sqrt() expects 1 argument");
        if (func_args[0] < 0) throw std::runtime_error("sqrt() expects argument value >= 0");
        d = sqrt(func_args[0]);
    }
    else if (s == "pow") {
        if (func_args.size() != 2) throw std::runtime_error("pow() expects 2 arguments");
        d = func_args[0];
        auto multiplier = func_args[0];
        int p = ppp::narrow_cast<int>(func_args[1]);
        for (; p > 1; --p) {
            d *= multiplier;
        }
    }
    else {
        throw std::runtime_error("unknown function");
    }
    return d;
}

//------------------------------------------------------------------------------

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
    case let:
        return declaration();
    case func:
        return function(t.name);
    default:
        ts.putback(t);
        return expression();
    }
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate()
{
    constexpr char* prompt = "> ";  // indicate a prompt
    constexpr char* result = "= ";  // indicate a result

    while (true) try {
        std::cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get();
        if (t.kind == quit) return;
        ts.putback(t);
        std::cout << result << statement() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        clean_up_mess();
    }
}

//------------------------------------------------------------------------------

int main()
try {
    SET_IOSYNC;
    calculate();
    return 0;
}
catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch (...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}