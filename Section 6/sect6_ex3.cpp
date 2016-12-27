/*
  written by Jtaim
  date 19 Nov 2015
  Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup
 
  Section 6 exercise 3
  Added to Section 6 exercise 2
  Add the ability to do factorials
*/

#include "section6.h"

//------------------------------------------------------------------------------
class Token
{
public:
	char kind;			// what kind of token
	double value;		// for numbers: a value 
	Token(char ch)
		:kind(ch), value(0) { }
	Token(char ch, double val)
		:kind(ch), value(val) { }
};

//------------------------------------------------------------------------------
class Token_stream
{
public:
	// The constructor just sets full to indicate that the buffer is empty:
	Token_stream()			// make a Token_stream that reads from cin
		:full(false), buffer(0) {}
	Token get();			// get a Token (get() is defined elsewhere)
	void putback(Token t);	// put a Token back
private:
	bool full{ false };		// is there a Token in the buffer?
	Token buffer;			// here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------
// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (full)
	{
		error("putback() into a full buffer");
	}
	buffer = t;			// copy t to buffer
	full = true;		// buffer is now full
}

//------------------------------------------------------------------------------
Token Token_stream::get()
{
	// do we already have a Token ready?
	// remove token from buffer
	if (full)
	{       
		full = false;
		return buffer;
	}
	char ch;
	std::cin >> ch;
	switch (ch)
	{
	case '=':					// for "print"
	case 'x':					// for "quit"
	case '{': case '}':case '(': case ')': case '+': case '-': case '*': case '/':
	case '!':
		return Token(ch);		// let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);	// put digit back into the input stream
		double val;
		std::cin >> val;		// read a floating-point number
		return Token('8', val);	// let '8' represent "a number"
	}
	default:
		error("Bad token");
		return -1;				//compile warning without wont get here
	}
}

//------------------------------------------------------------------------------
// provides get() and putback() 
Token_stream ts;

//------------------------------------------------------------------------------
// declaration so that primary() can call expression()

double expression();
double factorial();
//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '{':					// handle '{' expression '}'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}')
		{
			error("'}' expected");
		}
		return d;
	}
	case '(':					// handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
		{
			error("')' expected");
		}
		return d;
	}
	case '+':					// so can use positive number
		return +primary();
	case '-':					// so can use negative unary number
		return -primary();
	case '!':					// if have factorial with no primary before it
		std::cin.putback('1');		// a 1 back into cin stream because a 0 or 1 factorial is 1
		return primary();
	case '8':					// we use '8' to represent a number
		return t.value;			// return the number's value
	default:
		error("primary expected");
		return -1;				//compile warning without wont get here
	}
}

//------------------------------------------------------------------------------
// deal with * and /
// % not implemented yet
double term()
{
	double left = factorial();
	Token t = ts.get();			// get the next token from token stream
	while (true)
	{
		switch (t.kind)
		{
		case '*':
		{
			left *= factorial();
			t = ts.get();
			break;
		}
		case '/':
		{
			double d = factorial();
			if (left == 0)
			{
				error("divide by zero");
			}
			left /= d;
			t = ts.get();
			break;
		}
		default:
		{
			ts.putback(t);		// put t back into the token stream
			return left;
		}
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();		// read and evaluate a Term
	Token t = ts.get();			// get the next token from token stream
	while (true)
	{
		switch (t.kind)
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
			ts.putback(t);		// put t back into the token stream
			return left;		// finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

int main()
{
	using std::cout;
	using std::cin;

	try
	{

		cout << "Welcome to our simple calculator.\n"
			<< "Please enter expressions using floating-point numbers.\n"
			<< "Operations available are +, -, *, / and !.\n"
			<< "Can change order of operations using {} and ().\n"
			<< "Use the = to show results and x to exit.\n\n";

		double val = 0;
		while (cin)
		{
			Token t = ts.get();
			// 'x' for quit
			if (t.kind == 'x')
			{
				break;
			}
			// '=' for "print now"
			else if (t.kind == '=')
			{
				cout << val << '\n';
			}
			else
			{
				ts.putback(t);
				val = expression();
			}
		}
		keep_window_open();
	}
	catch (std::exception& e) {
		std::cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		std::cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
}

// factorial tighter bound than * and /
double factorial()
{
	int left = static_cast<int>(primary());
	Token t = ts.get();
	while (true)
	{
		if (t.kind == '!')
		{
			std::cout << "warning factorial will truncate floats to integer values\n";
			if (left < 0)
			{
				error("factorial can not be negative");
				return -1;				//compile warning without wont get here
			}
			else if (left == 0)
			{
				return left == 1;
			}
			else
			{
				int temp = 1;
				for (int i = left; i != 0; --i)
				{
					temp *= i;
				}
				t = ts.get();
				left = temp;
			}
		}
		else
		{
			ts.putback(t);
			return left;
		}
	}
}
