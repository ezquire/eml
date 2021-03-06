@page build Build
@section requirement Requirement
@subsection compiler A C++ compiler
Recent version of [Visual Studio](https://www.visualstudio.com/), [GCC](https://gcc.gnu.org/), and [Clang](https://clang.llvm.org/) should be find.

@subsection cmake CMake 3.8+
CMake is the build tool used for this projects.

@subsection conan Conan
To install third-party dependencies, you need [Conan](https://conan.io/).

@section start Quick Start
I assume you already have a recent version of CMake and a C++17 compiler. After those, the first thing you should do is installing Conan following the instruction [here](https://docs.conan.io/en/latest/installation.html).

Then go to the folder of this project and puts:

``` sh
mkdir build && cd build
conan install ..
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

Passing additional argument to `conan` or `cmake` when you need.
