#pragma once
#include <cstdint>
#include <iostream>

using u64 = uint64_t;

enum Color 
{
    WHITE, BLACK, BOTH
};

enum Piece
{
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

class Board
{
    private:

    u64 bitboards[2][6];
    u64 occupancies[3];

    Color turn;
    const char Pieces[2][6] = 
    {
        {'P', 'N', 'B', 'R', 'Q', 'K'}, //White Pieces[0] are uppercase
        {'p', 'n', 'b', 'r', 'q', 'k'}  //Black Pieces[1] are lowercase
    };

    public:
    
    Board();
    void setPiece(int color, int piece, int square);
    void initStartingPosition();
    void print() const;
    
    void updateOccupancies(); 
    inline u64 getPieceBitboard(int color, int piece) const {return bitboards[color][piece];}
    inline u64 getOccupancy(int color) const {return occupancies[color];}
    inline Color getSide() const {return turn;}
};