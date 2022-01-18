//Written by Jtaim
//Date 15 Dec 2018
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
	copied from drill 11 removed drill 10 stuff
	also added modulo
	section 7 exercise 1
	allow underscores in the calculator's variable names
*/

#include "../includes/ppp.h"

//------------------------------------------------------------------------------

const char number = '8';    // t.kind == number means that t is a number Token.
const char quit = 'q';      // t.kind == quit means that t is a quit Token.
const std::string declexit = "exit";
const char print = ';';     // t.kind == print means that t is a print Token.

const char name = 'a';      // name token
const char let = 'L';       // declaration token
const std::string declkey = "let"; // declaration keyword
const char func = 'F';      // function Token

struct Token
{
	char kind;
	double value;
	std::string name;
	Token(char ch, double val = 0.0) :kind(ch), value(val), name("") {}
	Token(char ch, std::string s) :kind(ch), value(0.0), name(s) {}
};

//------------------------------------------------------------------------------

// place to hold variable name value
struct Variable
{
	std::string name;
	double value{};
};

// overload equality operator to simplify get, set and is_declared functions 
bool operator==(const Variable& v, const std::string s) { return v.name == s; }

// container for all the variables
std::vector<Variable> names;

// return the value of the Variable with the input name.
double get_value(const std::string s)
{
	auto vt_itr = std::find(names.cbegin(), names.cend(), s);
	if(vt_itr == names.cend()){
		ppp::error("get: undefined name ", s);
	}
	return vt_itr->value;
}

// set the Variable of the named to a double value.
void set_value(const std::string s, const double d)
{
	auto vt_itr = std::find(names.begin(), names.end(), s);
	if(vt_itr == names.cend()){
		ppp::error("set: undefined name ", s);
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
	if(is_declared(s)) ppp::error(s, " declared twice");
	names.push_back(Variable{s, d});
	return d;
}

//------------------------------------------------------------------------------

// place to hold valid Tokens from cin
class Token_stream
{
public:
	Token_stream() :full(false), buffer('\0') {}

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
	Token t{'\0'};
	if(full){
		full = false;
		t = buffer;
	} else{
		char ch;
		std::cin >> ch;
		switch(ch){
			case print:
			case quit:
			case '(':
			case ')':
			case '+':
			case '-':
			case '*':
			case '/':
			case ',':
			case '%':
				t.kind = ch;
				break;
			case '=':
				if(this->buffer.kind != let){
					const std::string s = (this->buffer.kind == name ? this->buffer.name : std::to_string(this->buffer.value));
					ppp::error(s, " can not be re-assigned");
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
				if(isalpha(ch) || ch == '_'){
					std::string s;
					s += ch;
					while(std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
					std::cin.putback(ch);
					if(s == declkey){
						t.kind = let;
					} else if(ch == '('){
						t.kind = func;
						t.name = s;
					} else if(s == declexit){
						t.kind = quit;
					} else{
						t.kind = name;
						t.name = s;
					}
				} else{
					ppp::error("Bad token");
				}
		}
	}
	return t;
}

void Token_stream::putback(const Token t)
{
	if(full){
		ppp::error("putback() into a full buffer");
	}
	buffer = t;
	full = true;
}

void Token_stream::ignore(const char c)
{
	if(full && c == buffer.kind){
		full = false;
	} else{
		full = false;
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail(), c);
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
	switch(t.kind){
		case '(':
			{
				d = expression();
				t = ts.get();
				if(t.kind != ')'){
					ppp::error("')' expected");
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
			ppp::error("primary expected");
	}
}

//------------------------------------------------------------------------------

double term()
{
	double left = primary();
	while(true){
		Token t = ts.get();
		switch(t.kind){
			case '*':
				left *= primary();
				break;
			case '/':
				{
					double d = primary();
					if(d == 0) ppp::error("divide by zero");
					left /= d;
					break;
				}
			case '%':
				{
					double d = primary();
					if(d == 0){
						ppp::error("divide by zero");
					}
					left = fmod(left, d);
					break;
				}
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
	while(true){
		Token t = ts.get();
		switch(t.kind){
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
	if(t.kind != name){
		ppp::error("name expected in declaration");
	}
	if(is_declared(t.name)){
		ppp::error(t.name, " declared twice");
	}
	Token t2 = ts.get();
	if(t2.kind != '='){
		ppp::error("= missing in declaration of ", t.name);
	}
	double d = expression();
	define_name(t.name, d);
	return d;
}

//------------------------------------------------------------------------------

double function(const std::string& s)
{
	Token t = ts.get();
	double d{};
	std::vector<double> func_args;
	if(t.kind != '('){
		ppp::error("expected '(', malformed function call");
	} else{
		do{
			t = ts.get();
			// see if any argument is a function call
			if(t.kind == func){
				t.kind = number;
				// recursive call
				t.value = function(t.name);
				ts.putback(t);
			}
			// check if empty arguments
			if(t.kind == ')'){
				break;
			} else{
				ts.putback(t);
			}
			// push valid function argument
			func_args.push_back(expression());
			t = ts.get();
			if(t.kind == ')'){
				break;
			}
			if(t.kind != ','){
				ppp::error("expected ')', malformed function call");
			}
		} while(t.kind == ',');
	}

	if(s == "sqrt"){
		if(func_args.size() != 1) ppp::error("sqrt() expects 1 argument");
		if(func_args[0] < 0) ppp::error("sqrt() expects argument value >= 0");
		d = sqrt(func_args[0]);
	} else if(s == "pow"){
		if(func_args.size() != 2) ppp::error("pow() expects 2 arguments");
		d = func_args[0];
		auto multiplier = func_args[0];
		auto p = ppp::narrow_cast<int>(func_args[1]);
		for(; p > 1; --p){
			d *= multiplier;
		}
	} else{
		ppp::error("unknown function");
	}
	return d;
}

//------------------------------------------------------------------------------

double statement()
{
	Token t = ts.get();
	switch(t.kind){
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
	const std::string prompt = "> ";  // indicate a prompt
	const std::string result = "= ";  // indicate a result

	while(true) try{
		std::cout << prompt;
		Token t = ts.get();
		while(t.kind == print) t = ts.get();
		if(t.kind == quit) return;
		ts.putback(t);
		std::cout << result << statement() << std::endl;
	}
	catch(std::runtime_error& e){
		std::cerr << e.what() << std::endl;
		clean_up_mess();
	}
}

//------------------------------------------------------------------------------

int main()
try{
	std::cin.sync_with_stdio(false);
	calculate();
	return 0;
}
catch(std::exception& e){
	std::cerr << "exception: " << e.what() << std::endl;
	ppp::keep_window_open();
	return 1;
}
catch(...){
	std::cerr << "exception\n";
	ppp::keep_window_open();
	return 2;
}