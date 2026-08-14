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

    occupancies[WHITE] = 0;
    occupancies[BLACK] = 0;
    occupancies[BOTH]  = 0;

    turn = WHITE;

    enPassantSquare = -1;
    castlingRights = WK | WQ | BK | BQ;
}

void Board::setPiece(int color, int piece, int square)
{
    set_bit(bitboards[color][piece], square);
}

void Board::initStartingPosition() 
{
    /*
        white pieces are at bottom
        black pieces at top
    */  
    
    for(int i{}; i < 8; i++) 
    {
        setPiece(WHITE, PAWN, 8 + i);
        setPiece(BLACK, PAWN, 48 + i);
    }

    setPiece(WHITE, KNIGHT, 1); setPiece(WHITE, KNIGHT, 6);
    setPiece(BLACK, KNIGHT, 57); setPiece(BLACK, KNIGHT, 62);

    setPiece(WHITE, BISHOP, 2); setPiece(WHITE, BISHOP, 5);
    setPiece(BLACK, BISHOP, 58); setPiece(BLACK, BISHOP, 61);

    setPiece(WHITE, ROOK, 0); setPiece(WHITE, ROOK, 7);
    setPiece(BLACK, ROOK, 56); setPiece(BLACK, ROOK, 63);

    setPiece(WHITE, QUEEN, 3);
    setPiece(BLACK, QUEEN, 59);

    setPiece(WHITE, KING, 4);
    setPiece(BLACK, KING, 60);

    updateOccupancies();
}

void Board::print() const 
{
    std::cout << "\n";

    for(int row{7}; row >= 0; --row) 
    {
        std::cout << row + 1 << "  ";
        
        for(int col{}; col < 8; ++col) 
        {
            int square{row * 8 + col};
            char ch{'.'};
            
            for(int c{}; c < 2; ++c)    
            {
                for (int p{}; p < 6; ++p) 
                {
                    if(get_bit(bitboards[c][p], square)) 
                    {
                        ch = Pieces[c][p];
                    }
                }
            }

            std::cout << ch << " ";
        }

        std::cout << "\n";
    }

    std::cout << "\n   a b c d e f g h\n\n";
}

void Board::updateOccupancies() 
{
    occupancies[WHITE] = 0;
    occupancies[BLACK] = 0;
    occupancies[BOTH]  = 0;

    for(int piece{PAWN}; piece <= KING; ++piece) 
    {
        occupancies[WHITE] |= bitboards[WHITE][piece];
        occupancies[BLACK] |= bitboards[BLACK][piece];
    }

    occupancies[BOTH] = occupancies[WHITE] | occupancies[BLACK];
}