#pragma once
#include <cstdint>
#include "BitUtils.hpp"

using u64 = uint64_t;

class MoveGenerator 
{
    private:
    
    //return a bitboard of all legal jumps from that square
    u64 knightAttacks[64];
    u64 kingAttacks[64];

    void generateLeaperMoves(u64 table[64], const int rankJumps[8], const int fileJumps[8]);

    public:

    MoveGenerator();    
    u64 getKnightAttacks(int square) const;
    u64 getKingAttacks(int square) const;
};