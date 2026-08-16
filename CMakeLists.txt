cmake_minimum_required(VERSION 3.15)

project(BitboardChess VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -O3 -march=native)
endif()

add_executable(ChessEngine 
    src/main.cpp 
    src/Board.cpp 
    src/MoveGenerator.cpp
    src/Evaluation.cpp
    src/Search.cpp
)