#include "Board.hpp"
#include "BitUtils.hpp"

using u64 = uint64_t;

Board::Board() 
{
    for(int i{}; i < 2; ++i)
    {
        for(int j{}; j < 6; ++j)
        {
            bitboards[i][j] = 0;
        }
    }
}

void Board::setPiece(int color, int piece, int square)
{
    set_bit(bitboards[color][piece], square);
}

