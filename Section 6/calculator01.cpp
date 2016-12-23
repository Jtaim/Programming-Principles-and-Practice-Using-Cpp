//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

#include "section6.h"

//------------------------------------------------------------------------------
class Token
{
public:
	char kind;					// what kind of token
	double value;				// for numbers: a value 
	Token(char ch)				// make a Token from a char
		:kind(ch), value(0)
	{
		//std::cout << "token only created\n";
	}
	Token(char ch, double val)	// make a Token from a char and a double
		:kind(ch), value(val)
	{
		//std::cout << "token and value created\n";
	}
};

//------------------------------------------------------------------------------
class Token_stream
{
public:
	// The constructor just sets full to indicate that the buffer is empty:
	Token_stream()		// make a Token_stream that reads cin
		:full(false), buffer(0)
	{
		//std::cout << "token_stream created\n";
	}
	Token get();		// get a Token
	void putback(Token t);
private:
	bool full{ false };
	Token buffer;
};

//------------------------------------------------------------------------------
void Token_stream::putback(Token t)
{
	// precondition check
	if (full)
	{
		error("putback() into full buffer");
	}
	buffer = t;
	full = true;
}

//------------------------------------------------------------------------------
Token Token_stream::get()	// read a token from cin
{
	// do we already have a Token ready
	if (full)
	{
		full = false;		// remove Token from buffer
		return buffer;
	}
	char ch;
	std::cin >> ch;			// note that >> skips whitespace (space, newline, tab, etc.)
	switch (ch)
	{
	case ';':		// for "print"
	case 'q':		// for "quit"
	case '(': case ')': case '*': case '/': case '+': case '-':
		return Token(ch);	// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);		// put digit back into the input stream
		double val;
		std::cin >> val;			// read a floating-point number
		return Token('8', val);		// let '8' represent "a number"
	}
	default:
		error("Bad token");
		return 0;
	}
}

Token_stream ts;		// provides get() and putback()

// Forward Function declarations -------------------------------------------------------
double expression();	// deal with + and -
double primary();		// deal with numbers and parentheses
double term();			// deal with * and /

//------------------------------------------------------------------------------
int main()		// main loop
{
	try {
		double val = 0;
		while (std::cin)
		{
			Token t = ts.get();
			if (t.kind == 'q')
			{
				break;
			}
			else if (t.kind == ';')
			{
				std::cout << "= " << val << '\n';
			}
			else
			{
				ts.putback(t);
				val = expression();
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		keep_window_open("~1");
		return 1;
	}
	catch (...)
	{
		std::cerr << "exception \n";
		keep_window_open("~2");
		return 2;
	}
	keep_window_open();
	return 0;
}

//------------------------------------------------------------------------------
double primary()	// deal with numbers and parentheses
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':    // handle '(' expression ')'
	{
		//std::cout << "()\n";
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
		{
			error("')' expected");
		}
		return d;
	}
	case '8':            // we use '8' to represent a number
		//std::cout << "number\n";
		return t.value;  // return the number's value
	case '-':
		//std::cout << "negative\n";
		return -primary(); //handle negative numbers
	case '+':
		//std::cout << "positive\n";
		return +primary(); //handle positive numbers if + enetered before a number
	default:
		error("primary expected");
		return 0;
	}
}

//------------------------------------------------------------------------------
double term()	// deal with * and /
{
	double left = primary();
	Token t = ts.get();		// get the next token
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			//std::cout << "expression(*)\n";
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			//std::cout << "expression(/)\n";
			double d = primary();
			if (d == 0)
			{
				error("divide by zero");
			}
			left /= d;
			t = ts.get();
			break;
		}
		default:
			//std::cout << "primary\n";
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------
double expression()		// deal with + and -
{
	double left = term();	// read and evaluate a Term
	Token t = ts.get();		// get the next token
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			//std::cout << "expression(+)\n";
			left += term();	// evaluate Term and add
			t = ts.get();
			break;
		case '-':
			//std::cout << "expression(-)\n";
			left -= term();	// evaluate Term and subtract
			t = ts.get();
			break;
		default:
			//std::cout << "term\n";
			ts.putback(t);
			return left;	// finally: no more + or -: return the answer
		}
	}
}

/*
// a simple expression grammar:
Expression:
Term
Expression "+" Term       // addition
Expression "–" Term       // subtraction
Term :
Primary
Term "*" Primary             // multiplication
Term "/" Primary             // division
Term "%" Primary            // remainder (modulo)
Primary :
Number
"(" Expression ")"            // grouping
Number :
	floating - point - literal
*/