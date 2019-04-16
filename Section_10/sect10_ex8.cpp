/*
	Written by Jtaim
	April 13 2019
	Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

	Section 10 Exercise 8
	Write a program that accepts two file names and produces a new file that is the contents of the first
	file followed by the contents of the second; that is, the program concatenates the two files.

	the files I used are the input and output text files from exercise 5
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../includes/ppp.h"

const std::vector<std::string> read_files{
	"sect10_ex5_in.txt",
	"sect10_ex5_out.txt"
};

const std::string combined_files{"sect10_ex8.txt"};

int main()
try{
	// setup the file to capture read files
	std::ofstream out_file{combined_files};
	if(!out_file) ppp::error("could not open ", combined_files);

	for(auto fn : read_files){
		out_file << "Contents of file " << fn << "\n";
		std::ifstream in_file{fn};
		if(!in_file) ppp::error("could not open ", fn);
		for(std::string data; std::getline(in_file, data);){
			out_file << data << "\n";
		}
		if(!in_file.eof()) ppp::error("Data corrupted");
		in_file.close();

		out_file << "\n\n\n";
	}

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