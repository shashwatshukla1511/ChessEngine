#pragma once
#include <cstdint>
#include "BitUtils.hpp"

using u64 = uint64_t;

enum Direction
{
    NORTH, SOUTH, EAST, WEST,
    NORTH_EAST, NORTH_WEST, SOUTH_EAST, SOUTH_WEST
};

class MoveGenerator 
{
    private:
    
    //return a bitboard of all legal jumps from that square
    u64 knightAttacks[64];
    u64 kingAttacks[64];
    u64 pawnAttacks[2][64];
    u64 rays[8][64];

    void generateLeaperMoves(u64 table[64], const int rankJumps[8], const int fileJumps[8]);
    void initPawnAttacks();
    void initRays();

    public:

    MoveGenerator();    

    u64 getKnightAttacks(int square) const;
    u64 getKingAttacks(int square) const;
    u64 getPawnAttacks(int color, int square) const;
    u64 getRookAttacks(int square, u64 occupied) const;
    u64 getBishopAttacks(int square, u64 occupied) const;
    u64 getQueenAttacks(int square, u64 occupied) const;
    
    u64 getRay(Direction dir, int square) const;
};