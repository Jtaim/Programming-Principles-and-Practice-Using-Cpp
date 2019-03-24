/*
    Written by Jtaim
    Mar 24 Jan 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 10 Drill 4
    Test program Point class. Using iostream operation for Point class.
    Save Point data to a file.
*/

#include "../includes/ppp.h"
#include "Point.h"

int main()
try{
    constexpr std::vector<Point>::size_type HOW_MANY{7};
    const std::string FILE{"my_data.txt"};

    std::cout << "Enter seven (x,y) pairs:\n";
    std::vector<Point> original_points;
    std::ofstream fout{FILE};

    if(!fout) ppp::error("Can't open output file ", FILE);
    while(original_points.size() < HOW_MANY){
        Point point;
        if(!(std::cin >> point)){
            if(std::cin.eof()) ppp::error("EOF found before filling required data");
            std::cout << "bad input try again\n";
            ppp::clear_cin_buffer();
        }
        else{
            original_points.push_back(point);
            fout << point;
        }
    }

    fout.close();

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