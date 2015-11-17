//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

#include "section6.h"

//------------------------------------------------------------------------------
class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }    
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------
class Token_stream {
public:
	Token_stream()  // make a Token_stream that reads cin
		:full(false), buffer(0) { } // The constructor just sets full to indicate that the buffer is empty:
	Token get();     // get a Token
	void putback(Token t);
private:
	bool full{ false };
	Token buffer;
};

//------------------------------------------------------------------------------
void Token_stream::putback(Token t)
{
	if (full) error("putback() into full buffer"); // precondition check
	buffer = t;
	full = true;
}

//------------------------------------------------------------------------------
Token Token_stream::get()    // read a token from cin
{
	if (full) {         // do we already have a Token ready
		full = false;   // remove Token from buffer
		return buffer;
	}
	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case ';':    // for "print"
	case 'q':    // for "quit"
	case '(': case ')': case '*': case '/': case '+': case '-':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	default:
		error("Bad token");
		return 0;  // will never get here just to suppress compile warning for not having return
	}
}

Token_stream ts;  // provides get() and putback()

// Forward Function declarations -------------------------------------------------------
double primary();     // deal with numbers and parentheses
double term();        // deal with * and /
double expression();  // deal with + and -

//------------------------------------------------------------------------------
int main()  // main loop
try {
	double val = 0;
	while (cin) {
		Token t = ts.get();
		if (t.kind == 'q') 
            break;
		if (t.kind == ';') {
			cout << "=" << val << '\n';
		}
		else {
			ts.putback(t);
            val = expression();
		}
	}
    keep_window_open("~0");
}
catch (exception& e) {
    cerr << e.what() << endl;
    keep_window_open ("~1");
    return 1;
}
catch (...) {
    cerr << "exception \n";
    keep_window_open ("~2");
    return 2;
}

//------------------------------------------------------------------------------
double primary()  // deal with numbers and parentheses
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
    case '-':  // handle negative numbers
        return -primary();
	case '8':            // we use '8' to represent a number
		return t.value;  // return the number's value
	default:
		error("primary expected");
		return 0;  // will never get here just to suppress compile warning for not having return
	}
}

//------------------------------------------------------------------------------
double term()  // deal with * and /
{
	double left = primary();
	Token t = ts.get();     // get the next token

	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------
double expression()  // deal with + and -
{
	double left = term();      // read and evaluate a Term
	Token t = ts.get();     // get the next token
	while (true) {
		switch (t.kind) {
		case '+':
			left += term();    // evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();    // evaluate Term and subtract
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;       // finally: no more + or -: return the answer
		}
	}
}