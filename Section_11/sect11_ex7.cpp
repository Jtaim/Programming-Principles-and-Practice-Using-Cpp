/*
    Written by Jtaim
    Date 23 Sept 2019
    Stroustrup, Bjarne. Programming: Principles and Practice Using C++. Pearson Education. Kindle Edition.

    Section 11 Exercise 7
    Write a program that replaces punctuation with whitespace.
    Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters.
    Don’t modify characters within a pair of double quotes (").
    For example, " - don't use the as-if rule." becomes " don t use the as if rule ".

    Modify the program from the previous exercise so that it replaces don't with do not, can't with cannot, etc.;
    leaves hyphens within words intact (so that we get “ do not use the as-if rule ”); and converts all characters to lower case.
    https://en.wikipedia.org/wiki/Contraction_(grammar)
    https://www.grammarly.com/blog/contractions/
    https://grammar.yourdictionary.com/style-and-usage/using-contractions.html
    https://www.thoughtco.com/contractions-commonly-used-informal-english-1692651
*/

#include "ppp.h"

using uchar = unsigned char;

constexpr char no_modify{'"'};
constexpr char replacement{' '};

std::unordered_map<std::string, std::string> contraction{
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

int main()
try {
    std::cout << "Please enter a string\n";
    std::string str;
    std::getline(std::cin, str);

    std::transform(str.begin(), str.end(), str.begin(),
                   [](uchar c) { return static_cast<uchar>(std::tolower(c)); });

    std::istringstream iss{str};
    std::ostringstream oss;

    for(std::string s; iss >> s; ) {
        auto search{contraction.find(s)};
        if(search != contraction.end()) {
            oss << search->second << " ";
        } else {
            const auto how_big{s.size()};
            for(std::string::size_type i{}; i < how_big; ++i) {
                auto ch{static_cast<uchar>(s.at(i))};
                switch(ch) {
                    case no_modify:
                        if((i + 2) < how_big && s.at(i + 2) == no_modify) {
                            oss << s.at(i + 1);
                            i += 2;
                        } else {
                            oss << ch;
                        }
                        break;
                    case '.':
                    case ';':
                    case ',':
                    case '?':
                    case '\'':
                        oss << replacement;
                        break;
                    case '-':
                        if(i != 0 && (i + 1) < how_big && std::isalpha(s.at(i - 1)) && std::isalpha(s.at(i + 1))) {
                            oss << s.at(i) << s.at(i + 1);
                            ++i;
                        } else {
                            oss << replacement;
                        }
                        break;
                    default:
                        oss << ch;
                }
            }
            oss << " ";
        }
    }

    std::cout << oss.str() << "\n";

    ppp::keep_window_open();
    return 0;
}
catch(std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}