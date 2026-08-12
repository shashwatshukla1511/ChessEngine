#include <iostream>
#include "Board.hpp"
#include "MoveGenerator.hpp"

int main() {
    std::cout << "Initializing Chess Engine...\n";
    
    MoveGenerator moveGen;

    std::cout << "Testing Leaper Refactor...\n";

    std::cout << "\nLegal Knight jumps from e4 (Square 28):";
    uint64_t knightMask = moveGen.getKnightAttacks(28);
    printBitboard(knightMask);

    std::cout << "Legal King moves from e4 (Square 28):";
    uint64_t kingMask = moveGen.getKingAttacks(28);
    printBitboard(kingMask);

    return 0;
}