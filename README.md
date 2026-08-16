# BitboardChess

A lightweight, from-scratch Chess Engine written in C++17. This project uses 64-bit integer masks (bitboards) to represent the board state and generate moves, prioritizing raw speed and low-level bitwise operations.

## Features

* **Bitboard Representation:** The entire board state is tracked using `uint64_t` bitboards, allowing for hardware-accelerated piece lookups and move calculations.
* **Pseudo-Legal Move Generation:** Fast generation of moves for all pieces, including sliding attacks, pawn double-pushes, promotions, and En Passant.
* **Negamax Search Tree:** The engine's "brain" utilizes a recursive Minimax algorithm (structured as Negamax) to look into the future.
* **Alpha-Beta Pruning:** Heavily optimizes the search tree by instantly discarding unviable branches, allowing the engine to calculate deeper faster.
* **Terminal Interface:** A built-in command-line game loop to play directly against the engine in the console.

## Prerequisites

* **C++17 Compiler:** GCC or Clang recommended.
* **CMake:** Version 3.15 or higher.

## Building the Engine

The project is built using CMake. To compile the engine for maximum performance (`-O3` and `-march=native`), run the following commands in the root directory:

```bash
mkdir build
cd build
cmake ..
make