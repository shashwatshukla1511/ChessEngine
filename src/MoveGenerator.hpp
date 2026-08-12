#pragma once
#include <cstdint>
#include "BitUtils.hpp"

using u64 = uint64_t;

class MoveGenerator 
{
    private:
    
    //knightAttacks[square] returns a bitboard of all legal jumps from that square
    u64 knightAttacks[64];
    void initKnightAttacks();

    public:

    MoveGenerator();
    uint64_t getKnightAttacks(int square) const;
};