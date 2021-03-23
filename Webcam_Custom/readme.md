You should follow the instructions to compile dlib:
http://dlib.net/compile.html

The best way to compile a program that uses dlib is to use CMake. 
For example, the following commands will compile the example programs on any operating system:

```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Note that you need to have a C++11 compiler installed on your system. 
There are free C++11 compilers for most operating systems. For example, 
Visual Studio is free on Windows and GCC is free and works well on Mac OS X and Linux systems. 
If you have multiple compilers/IDEs installed then you can tell CMake which one you want it to use via the -G option. 
