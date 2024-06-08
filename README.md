# GL Math Metal Library

# Introduction
The library **glm_metal** is a small wrapper library for adding Metal API specific
functionality to the `glm` math library. Specifically, it provides a set of projection
functions for computer graphics that satisfy Metal's normalized device coordinate system
for orthographic and perspective projections.

# Getting Started
To use this library in your project, there are two possible approaches.

## Copy The Files Into Your Project
The first approach is the simplest if your project is already using `glm`: copy the 
files `glm_metal.h` and `glm_metal.cpp` from the `glm_metal` folder into your
source tree.

## Integrate The Source Tree For The Entire Library Into Your Project
The second approach requires the `cmake` built tool. First, copy the source tree
into the source tree for your project. Then, in your `CMakeLists.txt` file, add the 
following line
```cmake
add_subdirectory(./path/to/glm_metal)
```
and the library is ready to use.

Anywhere in your project that you use the library, just include the header
```cplusplus
#include <glm_metal/glm_metal.h>
```
and you're set to use the library.

## Building The Project
To build the project, enter the source tree root and run the following commands
```sh
cmake -B build
cmake --build build
```

## Running The Test Suite
To run the test suite, build the project from the root of the source tree and then run
```sh
ctest --test-dir build
```
To run the test suit with more informative output, run
```sh
ctest --test-dir build --output-on-failure
```

# Dependencies
**glm_metal** has two external dependencies: **glm** and **googletest**. Both of 
these dependencies are vendored with the project so there is no need to include
the external dependencies yourself.
