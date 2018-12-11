/*
    Written by Jtaim
    Date 8 Dec 2018
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup
    Section 8 Exercise 1
*/

#include "../includes/ppp.hpp"
#include "token.h"
#include "symbol_table.h"

//using namespace calculator;

//------------------------------------------------------------------------------

double expression(calculator::Token_Stream &ts, calculator::Symbol_Table &vt);

//------------------------------------------------------------------------------

double primary(calculator::Token_Stream &ts, calculator::Symbol_Table &vt)
{
    calculator::Token t = ts.get();
    double d{};
    switch (t.kind) {
    case '(': {
        d = expression(ts, vt);
        t = ts.get();
        if (t.kind != ')') {
            throw std::runtime_error("')' expected");
        }
        break;
    }
    case '-':
        d = -1 * primary(ts, vt);
        break;
    case '+':
        d = primary(ts, vt);
        break;
    case calculator::number:
        d = t.value;
        break;
    case calculator::name:
        d = vt.get_value(t.name);
        break;
    default:
        throw std::runtime_error("primary expected");
    }
    return d;
}

//------------------------------------------------------------------------------

double term(calculator::Token_Stream &ts, calculator::Symbol_Table &vt)
{
    double left = primary(ts, vt);
    while (true) {
        calculator::Token t = ts.get();
        switch (t.kind) {
        case '*':
            left *= primary(ts, vt);
            break;
        case '/':
        {	double d = primary(ts, vt);
        if (d == 0) throw std::runtime_error("divide by zero");
        left /= d;
        break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double expression(calculator::Token_Stream &ts, calculator::Symbol_Table &vt)
{
    double left = term(ts, vt);
    while (true) {
        calculator::Token t = ts.get();
        switch (t.kind) {
        case '+':
            left += term(ts, vt);
            break;
        case '-':
            left -= term(ts, vt);
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double declaration(calculator::Token_Stream &ts, calculator::Symbol_Table &vt)
{
    calculator::Token t = ts.get();
    if (t.kind != calculator::name) {
        throw std::runtime_error("name expected in declaration");
    }
    if (vt.is_declared(t.name)) {
        throw std::runtime_error(t.name + " declared twice");
    }
    calculator::Token t2 = ts.get();
    if (t2.kind != '=') {
        throw std::runtime_error("= missing in declaration of " + t.name);
    }
    double d = expression(ts, vt);
    vt.declare(t.name, d);
    return d;
}

//------------------------------------------------------------------------------

double statement(calculator::Token_Stream &ts, calculator::Symbol_Table &vt)
{
    calculator::Token t = ts.get();
    switch (t.kind) {
    case calculator::let:
        return declaration(ts, vt);
    default:
        ts.putback(t);
        return expression(ts, vt);
    }
}

//------------------------------------------------------------------------------

void clean_up_mess(calculator::Token_Stream &ts)
{
    ts.ignore(calculator::print);
}

//------------------------------------------------------------------------------

void calculate()
{
    calculator::Token_Stream ts;
    calculator::Symbol_Table vt;

    constexpr char* prompt = "> ";
    constexpr char* result = "= ";  // used to indicate that what follows is a result

    while (true) try {
        std::cout << prompt;
        calculator::Token t = ts.get();
        while (t.kind == calculator::print) t = ts.get();
        if (t.kind == calculator::quit) return;
        ts.putback(t);
        std::cout << result << statement(ts, vt) << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        clean_up_mess(ts);
    }
}

//------------------------------------------------------------------------------

int main()
try {
    calculate();
    ppp::keep_window_open();
    return 0;
}
catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch (...) {
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}