<div align="center">

# WindowsOptimizer

A free and open-source Windows optimalization software.

</div>

There are a lot of free Windows optimalization scams out there and we want to provide a software that does the same for you, but for free. WindowsOptimizer does just that, while being fully open source, so if you don't trust us, you can check the code yourself and compile it on your machine. 

## Building

Use GNU Make to compile the project. The Makefile can build .exe from Linux, as long as `x86_64-w64-mingw32-g++` and `x86_64-w64-mingw32-binutils` are installed.

On Windows you can download `make` from [this website](https://gnuwin32.sourceforge.net/packages/make.htm).

> [!TIP]
> While the binary does compile on Linux, it is recommended to use normal Windows machine for testing, because Wine does not emulate all required stuff.

