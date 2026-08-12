#pragma once
#include <cstdint>
#include <cassert>
#include <iostream>

using u64 = uint64_t;

inline constexpr void set_bit(u64& bitboard, int square) 
{
    bitboard |= (1ll << square);
}

inline constexpr u64 get_bit(u64 bitboard, int square) 
{   
    return bitboard & (1ll << square);
}

inline constexpr void clear_bit(u64& bitboard, int square) 
{
    bitboard &= ~(1ll << square);
}

inline int get_lsb(uint64_t b) 
{
    return (b? __builtin_ctzll(b): -1);
}

inline int get_msb(uint64_t b) 
{
    return (b? 63 - __builtin_clzll(b): -1);
}

inline void printBitboard(u64 bitboard) 
{
    std::cout << "\n";

    for(int row{7}; row >= 0; --row) 
    {
        std::cout << row + 1 << "  ";

        for(int col{}; col < 8; ++col) 
        {
            int square{row * 8 + col};

            if(get_bit(bitboard, square)) 
                std::cout << "1 ";

            else 
                std::cout << ". ";
        }

        std::cout << "\n";
    }

    std::cout << "\n   a b c d e f g h\n\n";
}