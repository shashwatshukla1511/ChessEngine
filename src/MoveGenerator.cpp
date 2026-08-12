#include "MoveGenerator.hpp"
#include "BitUtils.hpp"

using u64 = uint64_t;

MoveGenerator::MoveGenerator() 
{
    initKnightAttacks();
}

void MoveGenerator::initKnightAttacks() 
{
    int rankJumps[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int fileJumps[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for(int square{}; square < 64; ++square) 
    {
        knightAttacks[square] = 0;

        int row{square/8};
        int col{square % 8};

        for(int i{}; i < 8; ++i) 
        {   
            int nrow{row + rankJumps[i]};
            int ncol{col + fileJumps[i]};

            if(nrow >= 0 && nrow <= 7 && ncol >= 0 && ncol <= 7) 
            {
                int targetSquare{row * 8 + col};
                set_bit(knightAttacks[square], targetSquare);
            }
        }
    }
}

u64 MoveGenerator::getKnightAttacks(int square) const 
{
    return knightAttacks[square];
}