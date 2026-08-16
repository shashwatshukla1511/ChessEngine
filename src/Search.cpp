#include "Search.hpp"
#include "Evaluation.hpp"
#include "MoveGenerator.hpp"
#include "MoveList.hpp"

using u16 = uint16_t;
constexpr int inf = 1e6;

int Search::search(const Board& board, int depth, int alpha, int beta)
{
    if(depth == 0)
    {
        return Evaluation::evaluate(board);
    }

    MoveList moveList{};
    MoveGenerator moveGen{};
    moveGen.generateMoves(board, moveList);

    if(moveList.count == 0)
    {
        return 0; 
    }

    int maxScore{-inf};

    for(int i{}; i < moveList.count; ++i)
    {
        Board nextBoard{board}; 
        nextBoard.makeMove(moveList.moves[i]);
        
        int score{-search(nextBoard, depth - 1, -beta, -alpha)};

        maxScore = std::max(maxScore, score);
        alpha = std::max(alpha, maxScore);

        if(alpha >= beta)
        {
            break; //Alpha-beta cutoff
        }
    }

    return maxScore;
}

u16 Search::getBestMove(const Board& board, int depth)
{
    MoveList moveList{};
    MoveGenerator moveGen{};
    moveGen.generateMoves(board, moveList);

    int bestScore{-inf};
    u16 bestMove{};
    int alpha{-inf};
    int beta{inf};
    
    for(int i{}; i < moveList.count; ++i)
    {
        Board nextBoard{board};
        nextBoard.makeMove(moveList.moves[i]);

        int score{-search(nextBoard, depth - 1, -beta, -alpha)};

        if(score > bestScore)
        {
            bestScore = score;
            bestMove = moveList.moves[i];
        }

        if(bestScore > alpha)
        {
            alpha = bestScore;
        }
    }

    return bestMove;
}