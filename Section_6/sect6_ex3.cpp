/*
  written by Jtaim
  date 9 Apr 2017
  Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

  Section 6 exercise 2  Add the ability to use {}
  Section 6 exercise 3  Add factorials
*/

#include "section6.h"

class Token
{
public:
	char kind;			// what kind of token
	double value;		// for numbers: a value 
	//constructors
	Token(char ch)
		:kind(ch), value(0)
	{}
	Token(char ch, double val)
		:kind(ch), value(val)
	{}
};

//------------------------------------------------------------------------------

class Token_stream
{
public:
	// The constructor just sets full to indicate that the buffer is empty:
	Token_stream()					// make a Token_stream that reads from cin
		:full(false), buffer(' ')
	{}	// no Token in buffer
	Token get();					// get a Token (get() is defined elsewhere)
	void putback(Token t);			// put a Token back
private:
	bool full;      				// is there a Token in the buffer?
	Token buffer;					// here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if(full){
		error("putback() into a full buffer");
	}
	buffer = t;       // copy t to buffer
	full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
	Token temp{' '};

	// do we already have a Token ready?
	if(full){
		full = false;
		temp = buffer;
	} else{
		char ch;
		std::cin >> ch;
		switch(ch){
			case ';':				// for "print"
			case 'q':				// for "quit"
			case '!': case '{': case '}':
			case '(': case ')': case '*': case '/': case '+': case '-':
				temp.kind = ch;
				break;
			case '.':
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				{
					std::cin.putback(ch);	// put digit back into the input stream
					double val;
					std::cin >> val;		// read a floating-point number
					temp.kind = '8';
					temp.value = val;
					break;
				}
			default:
				error("Bad token");
		}
	}
	return temp;
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------
// deal with numbers and parentheses
double primary()
{
	double temp{};  // temp storage for the returns

	Token t = ts.get();
	switch(t.kind){
		case '{':			// handle '{' expression '}'
			{
				double d = expression();
				t = ts.get();
				if(t.kind != '}'){
					error("'}' expected");
				}
				temp = d;
				break;
			}
		case '(':			// handle '(' expression ')'
			{
				double d = expression();
				t = ts.get();
				if(t.kind != ')'){
					error("')' expected");
				}
				temp = d;
				break;
			}
		case '-':			// deal with - unary operator
			temp = -1 * primary();
			break;
		case '+':			// deal with + unary operator
			temp = primary();
			break;
		case '!':					// if have factorial with no primary before it
			std::cin.putback('!');	// a 1 back into cin stream because a 0 or 1 factorial is 1
			temp = 0;
			break;
		case '8':			// we use '8' to represent a number
			temp = t.value;	// return the number's value
			break;
		default:
			error("primary expected");
	}
	return temp;
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// factorial tighter bound than * and /
double factorial()
{
	double left = primary();
	Token t = ts.get();
	if(t.kind == '!'){
		std::cout << "warning factorial will truncate floats to integer values\n";
		auto fact = narrow_cast<long long, double>(left);
		if(fact < 0){
			error("factorial can not be negative");
		} else if(fact == 0){
			left = 1.0;
		} else{
			decltype(fact) temp = 1;
			for(long long i = 1; i <= fact; ++i){
				temp *= i;
				// no overflow check
			}
			left = narrow_cast<double, long long>(temp);
		}
	} else{
		ts.putback(t);
	}
	return left;
}

// deal with * and /
// % not implemented yet
double term()
{
	double left = factorial();
	Token t = ts.get();			// get the next token from token stream
	while(true){
		switch(t.kind){
			case '*':
				left *= factorial();
				t = ts.get();
				break;
			case '/':
				{
					double d = factorial();
					if(d == 0){
						error("divide by zero");
					}
					left /= d;
					t = ts.get();
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
	double left = term();		// read and evaluate a Term
	Token t = ts.get();			// get the next token from token stream
	while(true){
		switch(t.kind){
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
	try{
		std::cout << "\nWelcome to our simple calculator.\n"
			<< "Please enter expressions using floating-point numbers.\n"
			<< "Operations available are +, -, *, / and !.\n"
			<< "Can change order of operations using ( ) and or { }.\n"
			<< "Use the ; to show results and q to exit.\n\n";
		double val{};
		while(std::cin){
			Token t = ts.get();
			if(t.kind == 'q'){	// 'q' for quit
				std::cout << "Bye\n";
				break;
			}
			if(t.kind == ';'){	// ';' for "print now"
				std::cout << "= " << val << '\n';
			} else{
				ts.putback(t);
				val = expression();
			}
		}
	}
	catch(std::exception& e){
		std::cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch(...){
		std::cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
	keep_window_open();
	return 0;
}

