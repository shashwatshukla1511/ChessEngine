cmake_minimum_required(VERSION 3.15)

# Name your project 
project(BitboardChess VERSION 1.0)

# Enforce C++17 standard (gives us access to modern features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add compiler flags for strict warnings and maximum performance
# -O3 and -march=native are crucial for chess engine speed
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -O3 -march=native)
endif()

# Tell CMake to compile main.cpp into an executable named "ChessEngine"
add_executable(ChessEngine src/main.cpp src/Board.cpp src/MoveGenerator.cpp)