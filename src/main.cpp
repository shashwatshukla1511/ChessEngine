#include <iostream>
#include "Board.hpp"
#include "MoveGenerator.hpp"
#include "Move.hpp" 

int main() 
{
    std::cout << "Testing 16-bit Move Encoding...\n\n";
    
    int startSquare = 52; 
    int endSquare = 59;   
    int moveFlag = PROMOTE_QUEEN_CAPTURE; 

    u16 move = encodeMove(startSquare, endSquare, moveFlag);

    std::cout << "Packed Move Integer: " << move << "\n\n";

    std::cout << "--- Decoding ---\n";
    std::cout << "Source Square: " << getSource(move) << "\n";
    std::cout << "Target Square: " << getTarget(move) << "\n";
    std::cout << "Move Flag: " << getFlag(move) << "\n";

    return 0;
}