# AI disclosure: build boilerplate only. No compiler logic.
cmake_minimum_required(VERSION 3.16)

project(compiler_group_thirteen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lexer STATIC
    src/lexer/Lexer.cpp
)

target_include_directories(lexer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer
)

add_executable(compiler
    src/main.cpp
)

target_link_libraries(compiler PRIVATE lexer)
