#pragma once
#include <cstdint>
#include <cassert>

inline constexpr void set_bit(uint64_t& bitboard, int square) 
{
    bitboard |= (1ULL << square);
}

inline constexpr uint64_t get_bit(uint64_t bitboard, int square) 
{   
    return bitboard & (1ULL << square);
}

inline constexpr void clear_bit(uint64_t& bitboard, int square) 
{
    bitboard &= ~(1ULL << square);
}