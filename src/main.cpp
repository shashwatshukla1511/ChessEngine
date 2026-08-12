#include <iostream>
#include "Board.hpp"
#include "MoveGenerator.hpp"

int main() 
{
    std::cout << "Initializing Chess Engine...\n";
    
    MoveGenerator moveGen;

    std::cout << "\nWhite Pawn attacks from e4 (Square 28):";
    u64 whitePawnMask = moveGen.getPawnAttacks(0, 28);
    printBitboard(whitePawnMask);

    std::cout << "Black Pawn attacks from e4 (Square 28):";
    u64 blackPawnMask = moveGen.getPawnAttacks(1, 28);
    printBitboard(blackPawnMask);   
    
    return 0;
}