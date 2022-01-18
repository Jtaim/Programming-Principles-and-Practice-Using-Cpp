#include "Punct_stream.h"
#include <algorithm>

void Punct_stream::whitespace(const std::string &s)
{
    white = s;
}

void Punct_stream::add_white(char c)
{
    white += c;
}

bool Punct_stream::is_whitespace(const char c) const
{
    if(white.find(c) != std::string::npos) {
        return true;
    }
    return false;
}

void Punct_stream::case_sensitive(bool b)
{
    sensitive = b;
}

bool Punct_stream::is_case_sensitive() const
{
    return sensitive;
}

Punct_stream& Punct_stream::operator>>(std::string &s)
{
    // try to read from buffer
    while(!(buffer >> s)) {
        if(buffer.bad() || !source.good()) {
            return *this;
        }
        buffer.clear();
        std::string line;
        getline(source, line);
        line = contraction_check(line);

        // do character replacement as needed:
        std::ostringstream oss;
        for(std::string::size_type i{}; i < line.size(); ++i) {
            auto ch{line.at(i)};
            if(ch == no_modify) {
                if((i + 2) < line.size() && line.at(i + 2) == no_modify) {
                    oss << line.at(i + 1);
                    i += 2;
                } else {
                    oss << ch;
                }
            } else if(ch == '-') {
                if(i != 0 && (i + 1) < line.size() && std::isalpha(line.at(i - 1)) && std::isalpha(line.at(i + 1))) {
                    oss << line.at(i) << line.at(i + 1);
                    ++i;
                } else {
                    oss << space;
                }
            } else if(is_whitespace(ch)) {
                oss << space;
            } else {
                oss << ch;
            }
        }
        if(!sensitive) {
            std::transform(line.begin(), line.end(), line.begin(),
                           [](unsigned char c) { return static_cast<unsigned char>(std::tolower(c)); });
        }
        buffer.str(oss.str());
    }
    return *this;
}

Punct_stream::operator bool()
{
    return !(source.fail() || source.bad()) && buffer.good();
}

std::string Punct_stream::contraction_check(std::string &s)
{
    std::istringstream iss{s};
    std::ostringstream oss;
    for(std::string str; iss >> str; ) {
        auto search{contraction.find(str)};
        if(search != contraction.end()) {
            oss << search->second << " ";
        } else {
            oss << str << " ";
        }
    }
    return oss.str();
}
