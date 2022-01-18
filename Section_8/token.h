#ifndef TOKEN_H	// begin header guard
#define TOKEN_H

#include <string>

namespace ppp_calc
{

	constexpr char number{'8'};                // t.kind == number Token.
	constexpr char print{';'};                 // t.kind == print Token.

	constexpr char quit{'q'};                  // t.kind == quit Token.                                     
	constexpr char key_quit[]{"quit"};		   // quit keyword
	constexpr char help{'h'};                  // t.kind == help Token.
	constexpr char key_help[]{"help"};		   // help keyword

	constexpr char name{'a'};                  // t.kind = name of variable Token
	constexpr char let{'L'};                   // t.kind = declaration token
	constexpr char declkey[]{"let"};		   // declaration keyword
	constexpr char constant{'C'};              // t.kind = constant declaration Token
	constexpr char declkey_const[]{"const"};   // constant declaration keyword

	constexpr char func{'F'};				   // t.kind = function Token

	//------------------------------------------------------------------------------

	class Token
	{
	public:
		char kind;
		double value;
		std::string name;

		Token();
		Token(char ch, double val = 0.0);
		Token(char ch, std::string s);
		~Token();
	};

	//------------------------------------------------------------------------------

	class Token_Stream
	{
	public:
		Token_Stream();
		Token_Stream(std::istream& tsin); // Token_stream that reads from an istream
		~Token_Stream();

		Token get();
		void putback(const Token t);
		void ignore(const char c);

	private:
		bool full;      // is there a Token in the buffer?
		Token buffer;   // here is where we keep a Token put back using putback()
	};

} // ppp_calc

#endif	// close header guard