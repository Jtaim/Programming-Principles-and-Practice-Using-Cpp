//written by Jtaim
//date 31 Mar 2017
//Programming: Principles and Practice Using C++ Second Edition

/*
Section 4 exercise 7.
Modify the "mini calculator from exercise 5 to accept (just) single-digit numbers written as either digits
or spelled out.
*/

#include "section4.h"  // custom header

struct Calc {
    const char termination;
    const std::vector<char> ops;
    const std::vector<std::string> stn;
    bool term_fnd{ false };
    std::pair<int, int> nPair{ 0,0 };
    char oper{ '?' };

    Calc(char t, std::vector<char> o, std::vector<std::string> sn) :
        termination(t), ops(o), stn(sn) {}
};

bool get_numbers(Calc&);
bool get_num(int&, Calc&);
bool check_term(Calc&, std::string s = "");
void print_result(const int);

int main()
{
    using namespace std;

    Calc ccs{
        '|',
        { '+','-','*','/' },
        {	"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}
    };

    //pair<long long int, long long int> numbers{ 0, 0 };  // move to the struct
    while (ccs.term_fnd == false) {
        cout << "Enter 2 numbers and an operation (+, -, *, /). Use " << ccs.termination << " to exit.\n";
        cout << "Number entered must be between 0 and 9 either spelled out or as the number.\n\n";
        while (!get_numbers(ccs)) {
            if (ccs.term_fnd == false) {
                cout << "bad equation was entered. please re-enter or exit\n";
            }
            else { break; }
        }
        if (ccs.term_fnd == false) {
            cin >> ccs.oper;
            if (find(ccs.ops.begin(), ccs.ops.end(), ccs.oper) != ccs.ops.end()) {
                switch (ccs.oper) {
                case '+': print_result(ccs.nPair.first + ccs.nPair.second);
                    break;
                case '-': print_result(ccs.nPair.first - ccs.nPair.second);
                    break;
                case '*': print_result(ccs.nPair.first * ccs.nPair.second);
                    break;
                case '/':
                    if (ccs.nPair.second != 0) {
                        print_result(ccs.nPair.first / ccs.nPair.second);
                    }
                    else {
                        cout << "division by zero is not allowed.\n";
                    }
                    break;
                default:
                    simple_error("should not be here.\n");
                }
            }
            else {
                if (check_term(ccs) == false) {
                    cout << "bad operation entered. please re-enter equation or exit\n";
                }
            }
        }
    }
    cout << "Bye\n";
    keep_window_open();
    return 0;
}

bool get_numbers(Calc& cc)
{
    auto return_val{ true };
    if (get_num(cc.nPair.first, cc)) {
        if (get_num(cc.nPair.second, cc)) {
            return_val = true;
        }
        else { return_val = false; }
    }
    else { return_val = false; }
    return return_val;
}

bool get_num(int& n, Calc& cc)
{
    using std::cin;
    auto return_val{ false };
    auto number{ -1 };
    if (cin >> number) {
        if (number >= 0 && number <= 9) {
            n = number;
            return_val = true;
        }
        else {
            std::cout << "ops! out of range number.\n";
            if (cin.peek() != 0) {
                cin.ignore(256, '\n'); // clear anything remaining
            }
            return_val = false;
        }
    }
    // check if number is spelled out
    else {
        if (check_term(cc) == false) {
            cin.clear();	// clear io error because first check for an int above
            std::string enteredNum;
            cin >> enteredNum;
            // convert to lower
            std::transform(enteredNum.begin(), enteredNum.end(), enteredNum.begin(), [](unsigned char c) {
                return static_cast<unsigned char>(tolower(c));
            });
            // check if has a spelled out number
            auto num_index = std::find(cc.stn.begin(), cc.stn.end(), enteredNum);
            if (num_index != cc.stn.end()) {
                n = static_cast<int>(num_index - cc.stn.begin());
                return_val = true;
            }
            // check for termination
            else {
                check_term(cc, enteredNum);
                if (cin.peek() != 0) {
                    cin.ignore(256, '\n'); // clear anything remaining
                }
                return_val = false;
            }
        }
    }
    return return_val;
}

bool check_term(Calc& cc, std::string s)
{
    auto return_val{ false };
    if (std::cin.eof() || std::cin.bad())
    {
        cc.term_fnd = true;
        return_val = true;
    }
    else if (!s.empty() && (s.find(cc.termination) != std::string::npos)) {
        cc.term_fnd = true;
        return_val = true;
    }
    else {
        cc.term_fnd = false;
        return_val = false;
    }
    return return_val;
}

void print_result(const int result)
{
    std::cout << "Your result is " << result << std::endl;
}
