
//
// This is example code from Chapter 6.6 "Trying the first version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

#include "section6.h"

//------------------------------------------------------------------------------

class Token
{
public:
	char kind;        // what kind of token
	double value;     // for numbers: a value 
	Token(char ch, double val = 0.0)
		:kind(ch), value(val)
	{}
};

//------------------------------------------------------------------------------

Token get_token();

//------------------------------------------------------------------------------

double expression();  // read and evaluate a Expression

//------------------------------------------------------------------------------

double term();        // read and evaluate a Term

//------------------------------------------------------------------------------

double primary();     // read and evaluate a Primary

//------------------------------------------------------------------------------

int main()
try{
	while(std::cin){
		std::cout << "=" << expression() << '\n';
	}
	keep_window_open();
}
catch(std::exception& e){
	std::cerr << e.what() << std::endl;
	keep_window_open();
	return 1;
}
catch(...){
	std::cerr << "exception \n";
	keep_window_open();
	return 2;
}

//------------------------------------------------------------------------------

double expression()
{
	double left = term();      // read and evaluate a Term
	Token t = get_token();     // get the next token
	while(true){
		switch(t.kind){
			case '+':
				left += term();    // evaluate Term and add
				t = get_token();
				break;
			case '-':
				left -= term();    // evaluate Term and subtract
				t = get_token();
				break;
			default:
				return left;       // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

double term()
{
	double left = primary();
	Token t = get_token();     // get the next token

	while(true){
		switch(t.kind){
			case '*':
				left *= primary();
				t = get_token();
				break;
			case '/':
				{
					double d = primary();
					if(d == 0) error("divide by zero");
					left /= d;
					t = get_token();
					break;
				}
			default:
				return left;
		}
	}
}

//------------------------------------------------------------------------------

double primary()     // read and evaluate a Primary
{
	Token t = get_token();
	double temp{};
	switch(t.kind){
		case '(':    // handle '(' expression ')'
			{
				double d = expression();
				t = get_token();
				if(t.kind != ')') error("')' expected");
				temp = d;
				break;
			}
		case '8':            // we use '8' to represent a number
			temp = t.value;  // return the number's value
			break;
		default:
			error("primary expected");
	}
	return temp;
}

//------------------------------------------------------------------------------

Token get_token()
{
	char ch;
	std::cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)

	Token temp{' '};
	switch(ch){
		//not yet   case ';':  // for "print"
		//not yet   case 'q':  // for "quit"
		case '(': case ')': case '+': case '-': case '*': case '/':
			temp.kind = ch;        // let each character represent itself
			break;
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			{
				std::cin.putback(ch);   // put digit back into the input stream
				double val;
				std::cin >> val;        // read a floating-point number
				temp.kind = '8';        // let '8' represent "a number"
				temp.value = val;
				break;
			}
		default:
			error("Bad token");
	}
	return temp;
}

//------------------------------------------------------------------------------
