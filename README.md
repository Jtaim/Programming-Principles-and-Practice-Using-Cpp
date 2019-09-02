## Stroustrup, Bjarne. Programming: Principles and Practice Using C++.
#### Where to buy this book
[Link to PPP on Amazon.](https://www.amazon.com/Programming-Principles-Practice-Using-2nd/dp/0321992784/ref=sr_1_1?s=books&ie=UTF8&qid=1444058171&sr=1-1&keywords=Programming%3A+Principles+and+Practice+Using+C%2B%2B)

#### Why
I created this repository to share my solutions for the try its, review questions, drills, and exercises while fumbling my way through
Stroustrup, Bjarne. Programming: Principles and Practice Using C++ . Pearson Education. Kindle Edition.

#### Useful tools
- [Microsoft Visual Studio Community](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx) is what I will be using for the exercises from this book.
- [MinGW variant distribution](https://nuwen.net/mingw.html) that supports the latest GNU GCC compiler also is packaged with Boost and other neat libraries.
	Also, the distribution comes with the latest GNU Make program so you can create custom command line compiles from C++ files created via your favorite editor.

#### Notes
I will be using Microsoft Visual Studio Community to go through this book. 
I created a solution folder named PPP and added projects under the PPP solution for each section.
In the solution Configuration Properties I selected build for the section I'm working on and deselected the others or select current selection radial button.
If the sections contain multiple files with a main function I just select Exclude from Project for the files I'm not working on 
in the solution explorer tab.  Can always go back and add files back by selecting Include in Project. In the Solution Explorer tab you
can select view all files to see all the included and excluded files.

#### Deviations
If you're reading along you will notice I intentionally left out the header file mentioned in the book.  Instead I created a section header file for each of the sections 
because in the book's presented header file the functions have been implemented into most modern compilers, plus I wanted some experience dealing with custom header files.
If you want, you can get the header file from book's website [www.stroustrup.com/Programming](http://www.stroustrup.com/Programming/).</br>
<b>section 7</b></br>
Starting in this section, I will be using a general a header file in the project include folder for this section and the remaining sections.</br>
Right or wrong, I removed the syncing of the cpp streams to the c streams by defining [std::cin.sync_with_stdio(false)](https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio).
Normally all C++ streams have this set to true. This will provide better reliability into the cin.rdbuf()->in_avail() function.
Seems to be compiler dependent on how count is reported if set to true. Again right or wrong I don't know but I needed to see if anything is in the cin.rdbuf,  see ppp.h for additional details.
Also set up namespace (ppp) for functions unique to this books exercises.</br>
Exercises 9, 10 and 11 are incomplete.</br>
<b>section 9</b></br>
Exercises 16, 17 and 18 are incomplete.</br>
<b>section 10</b></br>
Exercises 9, 10 and 11 are incomplete.</br>
<b>section 11</b></br>
Skipping this section.  I might come back to finish.</br>
<b>section 12</b></br>
For help using the FLTK library I'm using [vcpkg](https://github.com/microsoft/vcpkg) C/C++ library manager.</br>
See section_12.vcxproj to see how I set FLTK includes and libs files.</br>
I have mine one folder up from my project root folder ($(SolutionDir)..\vcpkg\installed\x64-windows-static\include) this may vary depending on OS and other options, refer to [vcpkg documentation](https://vcpkg.readthedocs.io/en/latest/)  
Before including classes needed for this section you can compile and run the fltk_test_window.cpp file to check that you linked the libraries correctly.</br>

I'm working my way through the classes used for this section. The files from the books website don't seem to work correctly.
I'm currently debugging these files to get them to work, stay tuned.

#### Some web sites I found helpful
- [Markdown Cheat sheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Here-Cheatsheet)
- [isocpp.org](https://isocpp.org/)
- [C++ Core Guild lines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [GSL: Guideline Support Library](https://github.com/Microsoft/GSL)
- [CPP reference](http://en.cppreference.com/w/Main_Page)
- [LearnCpp.com](http://www.learncpp.com/)
- [fltk documentation](https://www.fltk.org/documentation.php)

#### Disclaimer
I'm new at this so any suggestions or comments are appreciated.
