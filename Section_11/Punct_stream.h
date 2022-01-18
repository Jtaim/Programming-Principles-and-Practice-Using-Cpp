#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

inline std::unordered_map<std::string, std::string> contraction{
    {"aren't", "are not"},
    {"can't", "cannot"},
    {"couldn't", "could not"},
    {"could've", "could have"},
    {"didn't", "did not"},
    {"doesn't", "does not"},
    {"don't", "do not"},
    {"hadn't", "had not"},
    {"hasn't", "has not"},
    {"haven't", "have not"},
    {"I'm", "I am"},
    {"I've", "I have"},
    {"isn't", "is not"},
    {"let's", "let us"},
    {"shan't", "shall not"},
    {"shouldn't", "should not"},
    {"should've", "should have"},
    {"they're", "they are"},
    {"they've", "they have"},
    {"wasn't", "was not"},
    {"we'll", "we will"},
    {"we're", "we are"},
    {"we've", "we have"},
    {"weren't", "were not"},
    {"who've", "who have"},
    {"won't", "will not"},
    {"wouldn't", "would not"},
    {"would've", "would have"},
    {"you're", "you are"},
    {"you've", "you have"}
};

class Punct_stream
{
public:
    Punct_stream(std::istream& is, const char c = ' ')
        : source{is}, space{c}, sensitive{true} { }

    // makes the whitespace set
    void whitespace(const std::string &s);
    void add_white(char c);
    bool is_whitespace(char c) const;
    void case_sensitive(bool b);
    bool is_case_sensitive() const;

    Punct_stream& operator>>(std::string &s);
    operator bool();
    std::string contraction_check(std::string &s);

private:
    std::istream& source;       // character source
    std::istringstream buffer;  // we let buffer do our formatting
    std::string white;          // characters considered “whitespace”
    bool sensitive;             // is the stream case-sensitive?};
    char no_modify{'"'};        // do not modify to whitespace token
    const char space{' '};
};
