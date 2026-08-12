#include <iostream>
#include <cstdint>

using u64 = uint64_t;

bool ibit(u64 board, int square)
{
    return (board & (1ull << (square)));
}

void printBoard(u64 board)
{

}   

int main() {
    std::cout << "Chess Engine Build Successful!" << std::endl;
    
    // A quick test to ensure our 64-bit integers are ready to go
    uint64_t testBitboard = 1ULL; 
    std::cout << "Size of bitboard: " << sizeof(testBitboard) << " bytes" << std::endl;
    
    return 0;
}