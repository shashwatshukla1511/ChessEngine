#include <iostream>
#include "Board.hpp"
#include "MoveGenerator.hpp"

int main() {
    std::cout << "Initializing Chess Engine...\n";
    
    MoveGenerator moveGen;

    std::cout << "\nNorth Ray from e4 (Square 28):";
    u64 northRay = moveGen.getRay(NORTH, 28);
    printBitboard(northRay);

    std::cout << "North-East Ray from e4 (Square 28):";
    u64 northEastRay = moveGen.getRay(NORTH_EAST, 28);
    printBitboard(northEastRay);

    return 0;
}