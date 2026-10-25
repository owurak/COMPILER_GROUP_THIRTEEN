# Build and Run

> AI disclosure: AI was used for build-documentation formatting. The instructions were reviewed and tested by the member.

## Requirements

- A C++17 compiler: g++ 9+, Clang, or MSVC
- CMake 3.16 or later
- Ninja build tool for the tested Windows/MSYS2 setup
- Git Bash on Windows to run the shell test script

## Build with CMake

Run commands from the repository root.

### Windows: MSYS2 g++ and Ninja

This configuration was tested with MSYS2 UCRT64 g++ and Ninja:

```cmd
cmake -G Ninja -B build -DCMAKE_CXX_COMPILER=C:\msys64\ucrt64\bin\g++.exe
cmake --build build