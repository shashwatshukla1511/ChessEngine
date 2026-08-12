#include <iostream>
#include "Board.hpp"
#include "MoveGenerator.hpp"

int main() 
{
    std::cout << "Initializing Chess Engine...\n";
    
    MoveGenerator moveGen;

    u64 occupied = 0;
    set_bit(occupied, 44); 
    set_bit(occupied, 12); 
    set_bit(occupied, 30); 
    set_bit(occupied, 25);
    
    std::cout << "\nOccupied Squares (Blockers):";
    printBitboard(occupied);

    std::cout << "Rook Attacks from e4 (Square 28) with Blockers:";
    u64 rookAttacks = moveGen.getRookAttacks(28, occupied);
    printBitboard(rookAttacks);

    return 0;
}