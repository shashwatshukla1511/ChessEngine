#pragma once
#include <cstdint>
#include "Board.hpp"

using u16 = uint16_t;

class Search
{
    public:
    
    static int search(const Board& board, int depth, int alpha, int beta);
    static u16 getBestMove(const Board& board, int depth);
};