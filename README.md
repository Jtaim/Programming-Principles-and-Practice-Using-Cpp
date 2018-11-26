## Programming: Principles and Practices Using C++ (PPP)
#### Where to buy this book
[Link to PPP on Amazon.](https://www.amazon.com/Programming-Principles-Practice-Using-2nd/dp/0321992784/ref=sr_1_1?s=books&ie=UTF8&qid=1444058171&sr=1-1&keywords=Programming%3A+Principles+and+Practice+Using+C%2B%2B)

#### Why
I thought GitHub would be a good place to share my solutions for the try its, review questions, drills, and exercises for the afore mentioned book.

#### Useful tools
- [Microsoft Visual Studio Community](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx)
- [MinGW variant distribution](https://nuwen.net/mingw.html) that supports the latest GNU GCC compiler also is packaged with Boost and other neat libraries.
	Also, the distribution comes with the latest GNU Make program so you can create custom command line compiles from C++ files created via your favorite editor.

#### Notes
I will be using Microsoft Visual Studio Community to go through this book. 
I created a solution folder named PPP and added projects under the PPP solution for each section.
In the solution Configuration Properties I selected build for the section I'm working on and deselected the others.
If the sections contain multiple files with a main function I just select Exclude from Project for the files I'm not working on 
in the solution explorer tab.  Can always go back and add files back by selecting Include in Project. In the Solution Explorer tab you
can select view all files to see all the included and excluded files.

#### Deviations
If you're reading along you will notice I intentionally left out the header file mentioned in the book.  Instead I created a section header file for each of the sections 
because in the book's presented header file the functions have been implemented into most modern compilers, plus I wanted some experience dealing with custom header files.
If you want, you can get the header file from book's website www.stroustrup.com/Programming

Starting with section 7, I started using and placed a header file in an include file for all sections to use from this section and remaining sections.
Also set up namespace (ppp) for functions unique to this books exercises.

#### Some web sites I found helpful
- [Markdown Cheat sheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Here-Cheatsheet)
- [isocpp.org](https://isocpp.org/)
- [C++ Core Guild lines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [GSL: Guideline Support Library](https://github.com/Microsoft/GSL)
- [CPP reference](http://en.cppreference.com/w/Main_Page)
- [LearnCpp.com](http://www.learncpp.com/)

#### Disclaimer
I'm new at this so any suggestions or comments are appreciated.
