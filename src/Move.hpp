#pragma once
#include <cstdint>

using u16 = uint16_t;

enum MoveFlag
{
    QUIET = 0,
    DOUBLE_PUSH = 1,
    KING_CASTLE = 2,
    QUEEN_CASTLE = 3,
    CAPTURE = 4,
    EN_PASSANT = 5,
    
    // Promotions (8-11)
    PROMOTE_KNIGHT = 8,
    PROMOTE_BISHOP = 9,
    PROMOTE_ROOK = 10,
    PROMOTE_QUEEN = 11,
    
    // Promotion Captures (12-15)
    PROMOTE_KNIGHT_CAPTURE = 12,
    PROMOTE_BISHOP_CAPTURE = 13,
    PROMOTE_ROOK_CAPTURE = 14,
    PROMOTE_QUEEN_CAPTURE = 15
};

/*
    Bits 0-5 -> Source Square (0-63)
    Bits 6-11 -> Target Square (0-63)
    Bits 12-15 -> Flags (0-15)    
*/

inline u16 encodeMove(int source, int target, int flag) 
{
    return (source & 0x3f) | ((target & 0x3f) << 6) | ((flag & 0xf) << 12);
}

inline int getSource(u16 move) 
{
    return move & 0x3f;
}

inline int getTarget(u16 move) 
{
    return (move >> 6) & 0x3f;
}

inline int getFlag(u16 move) 
{
    return (move >> 12) & 0xf;
}