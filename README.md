## Pong

This is a C++ version of the classic video game pong. It employs the SDL2 library for rendering geometry, text, and audio. Starting from rudimentary skeleton files, I created this game within 2 weeks as an assignment for my Game Design course in Spring 2025. During development, I learned the basics of SDL2 for 2D graphics rendering, as well as other fundamental concepts in game design like game clocks, gameplay loops, and difficulty curves.

## How to Run

The code package relies on CMake, a cross platform makefile generator. There exist versions of
CMake for windows, linux, and OSX. While generally each version behaves similarly, depending on
which C++ compiler you have you might need to add additional parameters. 

**For a linux system with a standard gnu c/c++ compiler:**

First, clone the repository to your local machine. 
1. make a subdirectory (under pong) named 'Release': mkdir Release
2. enter the subdir: cd Release
3. and generate the makefiles: cmake .. (mind the ‘..’)

**If on Windows:**

It is highly recommended to us linux (or OSX) if available on your machine. However, in case you
only have a Windows install, we recommend MSYS2 and mingw64. It is recommended if you have an
older MSYS2 install to remove it first and start with a clean version.
1) Install MSYS2: https://www.msys2.org/
2) Open the MSYS2 MINGW64 terminal (not the MSYS2 UCRT64 terminal)
2) Install mingw64: pacman -S mingw-w64-x86_64-toolchain (install all; 800Mb)
3) Install cmake: pacman -S mingw-w64-x86_64-cmake
4) Install git: pacman -S git
5) Optional: add <msys2 install path>/mingw64/bin to your path if you also want to be able to run
your code by double clicking. To add to your path, open "Edit environment variables" -> select
Path -> Edit -> New -> Browse
We will use the MSYS2 MINGW64 terminal for **all** steps.
1) To access your C-drive use: cd /c/
2) Next, git clone the code to your location of choice and use cd /c/<path> to
enter the location in MSYS2. If you get an error that git does not support 'https', then you probably
copy-pasted an invisible character before https; just delete all spaces between 'clone' and 'https',
and re-add a new space; this will delete the invisible character.
3) Make a directory 'Release' mkdir Release
2) Next, generate make files (capitalization of “MinGW Makefiles” matters!):
cd Release && cmake.exe -G "MinGW Makefiles" ..
3) The above step should complete without an error and find a C++ compiler. Next we can compile
the code: mingw32-make.exe
4) We can now run the game: ./main.exe
