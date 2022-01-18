/*
    Written by Jtaim
    Aug 3 2019
    Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

    Section 12 Exercise 2
    Draw a 100-by-30 Rectangle.
    Place the text “Howdy!” inside the Rectangle.

    https://graphicdesign.stackexchange.com/questions/4035/what-does-the-size-of-the-font-translate-to-exactly
*/

#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"
#include "utility.h"

int main()
try{
    using namespace Graph_lib;

    const Point top_left{100,100};
    Simple_window win{top_left,600,400,"Exercise #2"};

    const Point rectangle_location{250,185};
    const int rectangle_width{100};
    const int rectangle_height{30};
    Graph_lib::Rectangle r{rectangle_location, rectangle_width, rectangle_height};	// top left corner, width, height
    r.set_color(Color::Color_type::blue);
    win.attach(r);

    float h{}, v{};
    Fl::screen_dpi(h, v);

    for(int font_size{14}; font_size <= 40; ++font_size){
        Text text_out{rectangle_location, "Howdy"};
        text_out.set_font_size(font_size);
        float pixel_height = text_out.font_size() * h / 72;
        float new_location{};
        int new_y{};
        if(rectangle_height > pixel_height){
            new_location = rectangle_height - pixel_height;
        }
        else{
            new_location = pixel_height - rectangle_height;
        }
        new_y = static_cast<int>(rectangle_height / 2.0f + new_location / 2.0f);
        text_out.move(2, new_y);
        text_out.set_color(Color::Color_type::black);

        win.attach(text_out);

        win.wait_for_button();
        win.detach(text_out);
    }

    return 0;
}
catch(std::exception& e){
    std::cerr << R"(exception: )" << e.what() << std::endl;
    return 1;
}
catch(...){
    std::cerr << R"(exception)";
    return 2;
}