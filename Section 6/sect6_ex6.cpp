//written by Jtaim
//date 21 Nov 2015
//Programming: Principles and Practice Using C++ Second Edition

/*
A program that checks if a sentence is correct.
According to the grammar from 6.4.1
Assume sentence is terminated " . " surrounded by whitespace
Reply "ok" or "not ok"

Sentence:
	Noun Verb						// e.g., C++ rules
	Sentence Conjunction Sentence	// e.g., Birds fly but fish swim
Conjunction:
	"and"
	"or"
	"but"
Verb:
	"rules"
	"fly"
	"swim"
Noun:
	"birds"
	"fish"
	"c++"
Article:
	"the"
*/

#include "section6.h" // custom header

//------------------------------------------------------------------------------
class str {
private:
	string in_str;
public:
	str() : in_str(" ") { }
	str(string s) : in_str(s) { }
	bool compare(const vector<string> &vs);
};

bool str::compare(const vector<string> &vs)
{
	bool match = false;
	for (auto i : vs) {
		if (i == in_str) {
			match = true;
			break;
		}
	}
	return match;
}

//------------------------------------------------------------------------------
class str_stream {
private:
	bool full;
	str buffer;
public:
	str_stream()  // make a str_stream that reads cin
		: full(false), buffer("") { } // The constructor just sets full to indicate that the buffer is empty:
	str get();     // get a str
	void putback(str old);
};

//------------------------------------------------------------------------------
void str_stream::putback(str s)
{
	if (full) error("putback() into full buffer"); // precondition check
	buffer = s;
	full = true;
}

//------------------------------------------------------------------------------
str str_stream::get()    // read a string from cin
{
	if (full) {         // do we already have a string ready
		full = false;   // remove string from buffer
		return buffer;
	}
	string new_string;
	cin >> new_string;    // note that >> skips whitespace (space, newline, tab, etc.)
	transform(new_string.begin(), new_string.end(), new_string.begin(), ::tolower);  // make string lower case
	return str(new_string);
}

//------------------------------------------------------------------------------
str_stream ss;  // provides get() and putback()

//------------------------------------------------------------------------------
bool conjunction();

//------------------------------------------------------------------------------
bool article()
{
	vector<string> test{ "the" };
	str s = ss.get();
	if (s.compare(test)) return true;
	return false;
}

//------------------------------------------------------------------------------
bool noun()
{
	bool check = true;
	vector<string> test{ "birds","fish","c++" };
	str s = ss.get();
	if (s.compare(test) && check) return true;  // noun found
	ss.putback(s);
	if (article()) return noun(); // no noun but check if is article
	return false;
}

//------------------------------------------------------------------------------
bool verb()
{
	bool check = noun();
	if (check) {
		vector<string> test{ "rules","fly","swim" };
		str s = ss.get();
		if (s.compare(test) && check) return true;
	}
	return check;
}

//------------------------------------------------------------------------------
int main()
try
{
	cout << "Enter a sentence terminated with . surrounded by space.\n";
	if (conjunction()) {
		cout << "Sentence is OK.\n";
	}
	else {
		cout << "Sentence is Not OK.\n";
	}
	keep_window_open("~0");
	return 0;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}

//------------------------------------------------------------------------------
bool conjunction()
{
	bool check = verb();
	if (check) {
		vector<string> test{ "and","or","but" };
		str s = ss.get();
		if (s.compare(test) && check) {
			check = verb();
			s = ss.get();
		}
		test = { "." };
		if (s.compare(test) && check) return true;
	}
    return check;
}