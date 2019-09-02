#include "token.h"
#include "../includes/ppp.h"
#include <iostream>

namespace ppp_calc
{
	Token::Token()
		: kind('\0'), value(0.0), name("")
	{}

	Token::Token(char ch, double val)
		: kind(ch), value(val), name("")
	{}

	Token::Token(char ch, std::string s)
		: kind(ch), value(0.0), name(s)
	{}

	Token::~Token()
	{}

	//------------------------------------------------------------------------------

	Token_Stream::Token_Stream()
		: full(false), buffer()
	{
		// un-sync C++ stream from c streams
		std::cin.sync_with_stdio(false);
	}

	Token_Stream::Token_Stream(std::istream& tsin)
		: full(false), buffer()
	{
		// un-sync C++ stream from c streams
		std::cin.sync_with_stdio(false);
	}

	Token_Stream::~Token_Stream()
	{
		// redo-sync C++ stream from c streams
		std::cin.sync_with_stdio(true);
	}

	/// get a Token to place in the stream
	Token Token_Stream::get()
	{
		Token token{};
		if(full){
			full = false;
			token = buffer;
		} else{
			char ch;
			// get next character, eat spaces except new line is print
			do{
				std::cin.get(ch);
				if(ch == '\n') ch = print;
			} while(std::isspace(ch));
			switch(ch){
				case print:
				case '(': case ')':
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case ',':
				case '=':
					token.kind = ch;
					break;
				case '.':
				case '0': case '1': case '2': case '3': case '4':
				case '5': case '6': case '7': case '8': case '9':
					{
						std::cin.putback(ch);
						double val;
						std::cin >> val;
						token.kind = number;
						token.value = val;
					}
					break;
				default:
					if(isalpha(ch) || ch == '_'){
						std::string s;
						s += ch;
						while(std::cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')){
							s += ch;
						}
						std::cin.putback(ch);
						if(s == declkey){
							token.kind = let;
						} else if(s == declkey_const){
							token.kind = constant;
						} else if(ch == '('){
							token.kind = func;
							token.name = s;
						} else if(s == key_quit){
							token.kind = quit;
						} else if(s == key_help){
							token.kind = help;
						} else{
							token.kind = name;
							token.name = s;
						}
					} else{
						ppp::error("Bad token");
					}
			}
		}
		return token;
	}

	/// put a Token back
	void Token_Stream::putback(const Token t)
	{
		if(full){
			ppp::error("putback() into a full buffer");
		}
		buffer = t;
		full = true;
	}

	/// discard characters up to and including the given input kind token
	void Token_Stream::ignore(const char c)
	{
		if(full && c == buffer.kind){
			full = false;
		} else{
			full = false;
			std::cin.clear();
			// check if buffer is empty
			auto cb = std::cin.rdbuf()->in_avail();
			while(cb){
				char trash{};
				std::cin.get(trash);    //clear buffer
				if(c == trash) break;
				--cb;
			}
		}
	}

} // ppp_calc
