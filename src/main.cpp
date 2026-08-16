#include <iostream>
#include <string>
#include "Board.hpp"
#include "MoveGenerator.hpp"
#include "MoveList.hpp"
#include "Search.hpp"
#include "Move.hpp" 

using u16 = uint16_t;

// Helper to parse user input like "e2e4" into a 16-bit move
uint16_t parseMove(const std::string& moveStr, const Board& board)
{
    int sourceFile{moveStr[0] - 'a'};
    int sourceRank{moveStr[1] - '1'};
    int targetFile{moveStr[2] - 'a'};
    int targetRank{moveStr[3] - '1'};
    
    int sourceSquare{sourceRank * 8 + sourceFile};
    int targetSquare{targetRank * 8 + targetFile};
    
    MoveList moveList;
    MoveGenerator moveGen;
    moveGen.generateMoves(board, moveList);
    
    //Find the generated move that matches the user's squares
    for(int i{}; i < moveList.count; ++i)
    {
        u16 move{moveList.moves[i]};
        if(getSource(move) == sourceSquare && getTarget(move) == targetSquare)
        {
            return move;
        }
    }
    
    return 0; // Return 0 if the move is invalid or not found
}

//Helper to format a 16-bit move back into a string like "e7e5"
std::string formatMove(u16 move)
{
    int source{getSource(move)};
    int target{getTarget(move)};
    
    char sourceFile{static_cast<char>('a' + (source % 8))};
    char sourceRank{static_cast<char>('1' + (source / 8))};
    char targetFile{static_cast<char>('a' + (target % 8))};
    char targetRank{static_cast<char>('1' + (target / 8))};
    
    return std::string{sourceFile, sourceRank, targetFile, targetRank};
}

int main()
{
    Board board;
    board.initStartingPosition();
    
    while(true)
    {
        board.print(); 
        
        if(board.getSide() == WHITE)
        {
            std::cout << "Your move (e.g. e2e4): ";
            std::string userMove;
            std::cin >> userMove;
            
            u16 move{parseMove(userMove, board)};
            
            if(move == 0)
            {
                std::cout << "Invalid move! Please try again.\n";
                continue;
            }
            
            board.makeMove(move);
        }

        else
        {
            std::cout << "Engine is thinking...\n";
            
            // Search 4 moves deep into the future
            u16 bestMove{Search::getBestMove(board, 4)}; 
            
            if(bestMove == 0)
            {
                std::cout << "Game Over! No valid moves left.\n";
                break;
            }
            
            std::cout << "Engine plays: " << formatMove(bestMove) << "\n\n";
            board.makeMove(bestMove);
        }
    }

    return 0;
}