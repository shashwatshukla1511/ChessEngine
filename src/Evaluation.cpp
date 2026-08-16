#include "Evaluation.hpp"

int Evaluation::evaluate(const Board& board)
{
    int whiteScore{};
    int blackScore{};

    // PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
    int pieceValues[6]{100, 300, 300, 500, 900, 30000};

    for(int p{PAWN}; p <= QUEEN; ++p)
    {
        int whiteCount{__builtin_popcountll(board.getPieceBitboard(WHITE, p))};
        int blackCount{__builtin_popcountll(board.getPieceBitboard(BLACK, p))};

        whiteScore += (whiteCount * pieceValues[p]);
        blackScore += (blackCount * pieceValues[p]);
    }

    int evaluation{whiteScore - blackScore};

    // Negamax framework: Positive score always means the side to move is winning
    if(board.getSide() == BLACK)
    {
        evaluation = -evaluation;
    }
    
    return evaluation;
}