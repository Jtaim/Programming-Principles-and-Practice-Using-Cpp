/*
written by Jtaim
date 28 Jan 2018
Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

clean up calculator08buggy.cpp
Helpful comments removed.
We have inserted 3 bugs that the compiler will catch and 3 that it won't.

Section 7 Drill 1 Get the program to compile
Section 7 Drill 2 Add comments
*/

#include "section7.h"

/// class to hold object 
struct Token {
	char kind;			//what kind of token
	double value;		//for numbers
	std::string name;	//to hold varaible names
	Token() : kind(' '), value(0.0) {}
	Token(char ch) : kind(ch), value(0.0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch, std::string n) : kind(ch), name(n) {}
};

class Token_stream {
public:
	Token_stream() : full(false), buffer() {}	// make a Token_stream that reads from cin

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
private:
	bool full;
	Token buffer;
};

const char let = 'L';
const char quit = 'q';
const char print = ';';
const char number = '8';
const char name = 'a';
const std::string declkey = "let";
const std::string prompt = "> ";
const std::string result = "= ";

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	std::cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case print:
	case quit:
	case '=':
		return Token(ch);
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
	{	std::cin.putback(ch);
	double val;
	std::cin >> val;
	return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			std::string s;
			s += ch;
			while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			std::cin.putback(ch);
			if (s == declkey) return Token(let);
			//if (s == "quit") return Token(name);
			return Token( name, s );
		}
		error("Bad token");
		return Token();
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (std::cin >> ch)
		if (ch == c) return;
}

struct Variable {
	std::string name;
	double value;
	Variable(std::string n, double v) :name(n), value(v) { }
};

std::vector<Variable> names;

double get_value(std::string s)
{
	for (std::string::size_type i = 0; i < names.size(); ++i) {
		if (names[i].name == s) {
			return names[i].value;
		}
	}
	error("get: undefined name ", s);
	return 0.0;
}

void set_value(std::string s, double d)
{
	for (std::string::size_type i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(std::string s)
{
	for (std::string::size_type i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	double d = 0.0;
	switch (t.kind) {
	case '(':
	{
		d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	default:
		error("primary expected");
	}
	return d;
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		double d = 0.0;
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
			d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		case '%':
			d = primary();
			if (d == 0) error("divide by zero");
			left = fmod(left, d);
			t = ts.get();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

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
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error("name expected in declaration");
	if (is_declared(t.name)) error(t.name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", t.name);
	double d = expression();
	names.push_back(Variable(t.name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
	while (true) try {
		std::cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		std::cout << result << statement() << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		clean_up_mess();
	}
}

int main()
try {
	calculate();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "exception: " << e.what() << std::endl;
	char c;
	while (std::cin >> c&& c != ';');
	return 1;
}
catch (...) {
	std::cerr << "exception\n";
	char c;
	while (std::cin >> c && c != ';');
	return 2;
}
