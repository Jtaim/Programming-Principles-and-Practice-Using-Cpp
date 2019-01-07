/*
    Written by Jtaim
    Date 8 Dec 2018
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup
    Section 8 Exercise 1
*/

#include "../includes/ppp.h"
#include "token.h"
#include "symbol_table.h"

//using namespace calculator;

//------------------------------------------------------------------------------

double expression(calculator::Token_Stream &ts, calculator::Symbol_Table &vt);
double function(calculator::Token_Stream &ts, calculator::Symbol_Table &vt, const std::string &s);

//------------------------------------------------------------------------------

double primary(calculator::Token_Stream &ts, calculator::Symbol_Table &vt){
    calculator::Token t = ts.get();
    double d{};
    switch(t.kind){
        case '(':
        {
            d = expression(ts, vt);
            t = ts.get();
            if(t.kind != ')'){
                ppp::error("')' expected");
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
        case calculator::func:
            d = function(ts, vt, t.name);
            break;
        default:
            ppp::error("primary expected");
    }
    return d;
}

//------------------------------------------------------------------------------

double term(calculator::Token_Stream &ts, calculator::Symbol_Table &vt){
    double left = primary(ts, vt);
    while(true){
        calculator::Token t = ts.get();
        switch(t.kind){
            case '*':
                left *= primary(ts, vt);
                break;
            case '/':
            {
                double d = primary(ts, vt);
                if(d == 0) ppp::error("divide by zero");
                left /= d;
                break;
            }
            default:
                ts.putback(t);
        }
        return left;
    }
}

//------------------------------------------------------------------------------

double expression(calculator::Token_Stream &ts, calculator::Symbol_Table &vt){
    double left = term(ts, vt);
    while(true){
        calculator::Token t = ts.get();
        switch(t.kind){
            case '+':
                left += term(ts, vt);
                break;
            case '-':
                left -= term(ts, vt);
                break;
            case ',':
                break;
            default:
                ts.putback(t);
        }
        return left;
    }
}

//------------------------------------------------------------------------------

double declaration(calculator::Token_Stream &ts, calculator::Symbol_Table &vt, bool is_const){
    calculator::Token t = ts.get();
    if(t.kind != calculator::name){
        ppp::error("name expected in declaration");
    }
    if(vt.is_declared(t.name)){
        ppp::error(t.name, " declared twice");
    }
    calculator::Token t2 = ts.get();
    if(t2.kind != '='){
        ppp::error("= missing in declaration of ", t.name);
    }
    double d = expression(ts, vt);
    vt.declare(t.name, d, is_const);
    return d;
}

//------------------------------------------------------------------------------

double statement(calculator::Token_Stream &ts, calculator::Symbol_Table &vt){
    calculator::Token t = ts.get();
    double d{};
    switch(t.kind){
        case calculator::let:
            d = declaration(ts, vt, false);
            break;
        case calculator::constant:
            d = declaration(ts, vt, true);
            break;
        case calculator::name:
        {
            calculator::Token t2 = ts.get();
            if(t2.kind != '='){
                std::cin.putback(t2.kind);
                ts.putback(t);
                d = expression(ts, vt);
            }
            else{
                d = expression(ts, vt);
                vt.set_value(t.name, d);
            }
            break;
        }
        default:
            ts.putback(t);
            d = expression(ts, vt);
    }
    return d;
}

//------------------------------------------------------------------------------

void clean_up_mess(calculator::Token_Stream &ts){
    ts.ignore(calculator::print);
}

//------------------------------------------------------------------------------

void print_help();

//------------------------------------------------------------------------------

void calculate(){
    calculator::Token_Stream ts;
    calculator::Symbol_Table vt;

    const std::string prompt = "> ";
    const std::string result = "= ";  // used to indicate that what follows is a result

    calculator::Token t;
    while(t.kind != calculator::quit) try{
        std::cout << prompt;
        t = ts.get();
        while(t.kind == calculator::print) t = ts.get();
        switch(t.kind){
            case calculator::quit:
                break;
            case calculator::help:
                print_help();
                ppp::clear_cin_buffer();
                break;
            case ',':
                std::cout << result << statement(ts, vt) << std::endl;
                break;
            default:
                ts.putback(t);
                std::cout << result << statement(ts, vt) << std::endl;
        }
    }
    catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        clean_up_mess(ts);
    }
}

//------------------------------------------------------------------------------

int main()
try{
    calculate();
    ppp::keep_window_open();
    return 0;
}
catch(std::exception& e){
    std::cerr << "exception: " << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...){
    std::cerr << "exception\n";
    ppp::keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------

double func_availible(const std::string &s, const std::vector<double> &args){
    double d{};
    if(s == "sqrt"){
        if(args.size() != 1) ppp::error("sqrt() expects 1 argument");
        if(args.at(0) < 0) ppp::error("sqrt() expects argument value >= 0");
        d = sqrt(args.at(0));
    }
    else if(s == "pow"){
        if(args.size() != 2) ppp::error("pow() expects 2 arguments");
        d = args.at(0);
        auto multiplier = args.at(0);
        auto p = ppp::narrow_cast<int>(args.at(1));
        for(; p > 1; --p){
            d *= multiplier;
        }
    }
    else{
        ppp::error("unknown function");
    }
    return d;
}

double function(calculator::Token_Stream &ts, calculator::Symbol_Table &vt, const std::string &s){
    calculator::Token t = ts.get();
    std::vector<double> func_args;
    if(t.kind != '('){
        ppp::error("expected '(', malformed function call");
    }
    else{
        do{
            t = ts.get();
            // true check for arguments
            // false if no arguments
            if(t.kind != ')'){
                ts.putback(t);
                func_args.push_back(expression(ts, vt));
            }
        } while(t.kind != ')');
    }
    return func_availible(s, func_args);
}

//------------------------------------------------------------------------------

void print_help(){
    std::ostringstream os;
    os << "Welcome to our simple calculator.\n"
        << "- Please enter expressions using floating-point numbers.\n"
        << "- Operations available are +, -, *, /, %.\n"
        << "- Can change order of operations using ( ).\n"
        << "- Declare named variables with the let keyword. (let x = 10.5)\n"
        << "- Declare named constant variables with the constant keyword. (const PI = 3.14)\n"
        << "- Can reassign non constant named variables. (x = PI/2)\n"
        << "- Functions available are pow(arg, p) and sqrt(arg).\n"
        << "- Use the '" << calculator::print << "' or new line to show results.\n"
        << "- type " << calculator::quit << " to quit.\n\n";

    std::cout << os.str() << std::endl;
}