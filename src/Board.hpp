#pragma once
#include <cstdint>
#include <iostream>

using u64 = uint64_t;

enum Color 
{
    WHITE, BLACK
};

enum Piece
{
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

class Board
{
    private:

    u64 bitboards[2][6];
    const char Pieces[2][6] = {
        {'P', 'N', 'B', 'R', 'Q', 'K'}, //White Pieces are uppercase
        {'p', 'n', 'b', 'r', 'q', 'k'}  //Black Pieces are lowercase
    };

    public:

    Board();
    void setPiece(int color, int piece, int square);
    void print() const;
};