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

using point_type = Point<int>;

void Print(const std::vector<point_type>& points)
{
    for(const auto point : points){
        std::cout << point << "\n";
    }
}

int main()
try{
    constexpr std::vector<point_type>::size_type HOW_MANY{7};
    const std::string FILE{"my_data.txt"};

    std::cout << "Enter seven (x,y) pairs:\n";
    std::vector<point_type> original_points;
    std::ofstream fout{FILE};

    if(!fout) ppp::error("Can't open output file ", FILE);
    while(original_points.size() < HOW_MANY){
        point_type point;
        if(!(std::cin >> point)){
            if(std::cin.eof()){
                std::cout << "EOF found before getting required data amount";
                break;
            }
            std::cout << "bad input try again\n";
            ppp::clear_cin_buffer();
        }
        else{
            original_points.push_back(point);
            fout << point;
        }
    }

    fout.close();

    std::vector<point_type> processed_points;
    std::ifstream fin{FILE};

    if(!fin) ppp::error("Can't open input file ", FILE);
    // set size difference
    while(processed_points.size() < HOW_MANY - 1){
        point_type point;
        if(!(fin >> point)){
            if(fin.eof()){
                std::cout << "EOF found before reading required data amount";
                break;
            }
            if(fin.fail()) ppp::error("bad input data");
        }
        else{
            processed_points.push_back(point);
        }
    }

    std::cout << "Entered points:\n";
    Print(original_points);
    std::cout << "Retrieved from file points:\n";
    Print(processed_points);

    if(!(original_points.size() == processed_points.size())){
        std::cout << "Something's wrong!";
    }

    ppp::keep_window_open();
    return 0;
}
catch(std::exception& e){
    std::cerr << R"(exception: )" << e.what() << std::endl;
    ppp::keep_window_open();
    return 1;
}
catch(...){
    std::cerr << R"(exception)";
    ppp::keep_window_open();
    return 2;
}