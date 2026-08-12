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

    initPawnAttacks();
    initRays();
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

void MoveGenerator::initPawnAttacks() 
{
    for(int square{}; square < 64; ++square) 
    {
        pawnAttacks[0][square] = 0; 
        pawnAttacks[1][square] = 0; 

        int row{square/8};
        int col{square % 8};

        //white pawns only move up
        if(row < 7) 
        {
            //left attack
            if(col > 0) 
                set_bit(pawnAttacks[0][square], (row + 1) * 8 + (col - 1));

            //right attack
            if(col < 7) 
                set_bit(pawnAttacks[0][square], (row + 1) * 8 + (col + 1));
        }

        //black pawns only move down
        if(row > 0) 
        {
            //left attack
            if(col > 0) 
                set_bit(pawnAttacks[1][square], (row - 1) * 8 + (col - 1));

            //right attack
            if(col < 7) 
                set_bit(pawnAttacks[1][square], (row - 1) * 8 + (col + 1));
        }
    }
}

void MoveGenerator::initRays() 
{
    int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1}; 
    int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1}; 

    for(int square{}; square < 64; ++square) 
    {
        int row{square/8};
        int col{square % 8};

        for(int dir{}; dir < 8; ++dir) 
        {
            rays[dir][square] = 0;

            int r{row + dx[dir]};
            int c{col + dy[dir]};

            while(r >= 0 && r <= 7 && c >= 0 && c <= 7) 
            {
                int targetSquare{r * 8 + c};
                set_bit(rays[dir][square], targetSquare);
                    
                r += dx[dir];
                c += dy[dir];
            }
        }
    }
}

u64 MoveGenerator::getRookAttacks(int square, u64 occupied) const 
{
    u64 attacks{};
    u64 ray{}, blockers{};

    ray = rays[NORTH][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[NORTH][get_lsb(blockers)]);

    else 
        attacks |= ray;
    
    ray = rays[EAST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[EAST][get_lsb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[SOUTH][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[SOUTH][get_msb(blockers)]);
    
    else 
        attacks |= ray;

    ray = rays[WEST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[WEST][get_msb(blockers)]);

    else 
        attacks |= ray;

    return attacks;
}

u64 MoveGenerator::getBishopAttacks(int square, u64 occupied) const 
{
    u64 attacks{};
    u64 ray, blockers;

    ray = rays[NORTH_EAST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[NORTH_EAST][get_lsb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[NORTH_WEST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[NORTH_WEST][get_lsb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[SOUTH_EAST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[SOUTH_EAST][get_msb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[SOUTH_WEST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[SOUTH_WEST][get_msb(blockers)]);

    else 
        attacks |= ray;

    return attacks;
}

//Queen is Bishop and rook combined
u64 MoveGenerator::getQueenAttacks(int square, u64 occupied) const 
{
    return getRookAttacks(square, occupied) | getBishopAttacks(square, occupied);
}

u64 MoveGenerator::getPawnAttacks(int color, int square) const 
{
    return pawnAttacks[color][square];
}

u64 MoveGenerator::getKnightAttacks(int square) const 
{
    return knightAttacks[square];
}

u64 MoveGenerator::getKingAttacks(int square) const 
{
    return kingAttacks[square];
}

u64 MoveGenerator::getRay(Direction dir, int square) const 
{
    return rays[dir][square];
}