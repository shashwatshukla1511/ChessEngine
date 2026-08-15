#pragma once
#include <cstdint>
#include <iostream>

using u16 = uint16_t;
using u64 = uint64_t;

enum Color 
{
    WHITE, BLACK, BOTH
};

enum Piece
{
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

enum CastlingRights 
{
    WK = (1 << 0), // White Kingside  (0001)
    WQ = (1 << 1), // White Queenside (0010)
    BK = (1 << 2), // Black Kingside  (0100)
    BQ = (1 << 3)  // Black Queenside (1000)
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
    
    void makeMove(u16 move);
    int enPassantSquare; 
    int castlingRights;

    Board();
    void setPiece(int color, int piece, int square);
    void initStartingPosition();
    void print() const;

    void updateOccupancies(); 
    inline u64 getPieceBitboard(int color, int piece) const {return bitboards[color][piece];}
    inline u64 getOccupancy(int color) const {return occupancies[color];}
    inline Color getSide() const {return turn;}
};