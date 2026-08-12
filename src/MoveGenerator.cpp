#include "MoveGenerator.hpp"
#include "BitUtils.hpp"

using u64 = uint64_t;

MoveGenerator::MoveGenerator() 
{
    int dx_knight[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy_knight[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    generateLeaperMoves(knightAttacks, dx_knight, dy_knight);

    int dx_king[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy_king[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    generateLeaperMoves(kingAttacks, dx_king, dy_king);
}

void MoveGenerator::generateLeaperMoves(u64 table[64], const int dx[8], const int dy[8])
{
    for(int square{}; square < 64; ++square) 
    {
        table[square] = 0;

        int row{square/8};
        int col{square % 8};

        for(int i{}; i < 8; ++i) 
        {   
            int nrow{row + dx[i]};
            int ncol{col + dy[i]};

            if(nrow >= 0 && nrow <= 7 && ncol >= 0 && ncol <= 7) 
            {
                int targetSquare{nrow * 8 + ncol};
                set_bit(table[square], targetSquare);
            }
        }
    }
}

u64 MoveGenerator::getKnightAttacks(int square) const 
{
    return knightAttacks[square];
}

u64 MoveGenerator::getKingAttacks(int square) const 
{
    return kingAttacks[square];
}