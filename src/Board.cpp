#include "Board.hpp"
#include "BitUtils.hpp"

using u64 = uint64_t;

Board::Board() 
{
    for(int i{}; i < 2; ++i)
    {
        for(int j{}; j < 6; ++j)
        {
            bitboards[i][j] = 0;
        }
    }
}

void Board::setPiece(int color, int piece, int square)
{
    set_bit(bitboards[color][piece], square);
}

void Board::initStartingPosition() 
{
    /*
        White Pawns (Rank 2: indices 8-15)
        Black Pawns (Rank 7: indices 48-55)
    */  
    
    for(int i{}; i < 8; i++) 
    {
        setPiece(WHITE, PAWN, 8 + i);
        setPiece(BLACK, PAWN, 48 + i);
    }

    //Knights
    setPiece(WHITE, KNIGHT, 1); setPiece(WHITE, KNIGHT, 6);
    setPiece(BLACK, KNIGHT, 57); setPiece(BLACK, KNIGHT, 62);

    //Bishops
    setPiece(WHITE, BISHOP, 2); setPiece(WHITE, BISHOP, 5);
    setPiece(BLACK, BISHOP, 58); setPiece(BLACK, BISHOP, 61);

    //Rooks
    setPiece(WHITE, ROOK, 0); setPiece(WHITE, ROOK, 7);
    setPiece(BLACK, ROOK, 56); setPiece(BLACK, ROOK, 63);

    //Queens
    setPiece(WHITE, QUEEN, 3);
    setPiece(BLACK, QUEEN, 59);

    //Kings
    setPiece(WHITE, KING, 4);
    setPiece(BLACK, KING, 60);
}

void Board::print() const 
{
    std::cout << "\n";
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << rank + 1 << "  ";
        
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            char pieceChar = '.';
            
            for (int c = 0; c < 2; c++) {
                for (int p = 0; p < 6; p++) {
                    if (get_bit(bitboards[c][p], square)) {
                        pieceChar = Pieces[c][p];
                    }
                }
            }
            std::cout << pieceChar << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n   a b c d e f g h\n\n";
}