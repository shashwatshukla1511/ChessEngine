#include <iostream>
#include "Board.hpp"
#include "MoveGenerator.hpp"

int main() 
{
    std::cout << "Initializing Chess Engine...\n";
    
    MoveGenerator moveGen;

    std::cout << "Legal Knight jumps from e4 (Square 28):";
    uint64_t knightMask{moveGen.getKnightAttacks(28)};
    printBitboard(knightMask);  
    
    return 0;
}