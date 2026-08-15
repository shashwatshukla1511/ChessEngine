#include "Board.hpp"
#include "BitUtils.hpp"
#include "Move.hpp" 

using u16 = uint64_t;
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

void Board::makeMove(u16 move)
{
    int source{getSource(move)};
    int target{getTarget(move)};
    int flag{getFlag(move)};
    int side{turn};
    int enemySide{(side == WHITE) ? BLACK : WHITE};

    // 1. Find which piece is moving
    int movedPiece{-1};
    
    for(int p{PAWN}; p <= KING; ++p)
    {
        if(get_bit(bitboards[side][p], source))
        {
            movedPiece = p;
            break;
        }
    }

    // 2. Pick the piece up and place it on the target square
    clear_bit(bitboards[side][movedPiece], source);
    set_bit(bitboards[side][movedPiece], target);
    
    // Captures (Standard and Promotion Captures)
    if(flag == CAPTURE || (flag >= PROMOTE_QUEEN_CAPTURE && flag <= PROMOTE_KNIGHT_CAPTURE))
    {
        for(int p{PAWN}; p <= KING; ++p)
        {
            if(get_bit(bitboards[enemySide][p], target))
            {
                clear_bit(bitboards[enemySide][p], target);
                break;
            }
        }
    }

    //En Passant Capture
    if(flag == EN_PASSANT)
    {
        int captureSquare{(side == WHITE) ? target - 8 : target + 8};
        clear_bit(bitboards[enemySide][PAWN], captureSquare);
    }

    //Promotions
    if(flag >= PROMOTE_QUEEN && flag <= PROMOTE_KNIGHT_CAPTURE)
    {
        // Delete the pawn that just landed on the target square
        clear_bit(bitboards[side][PAWN], target);

        //Figure out which piece to promote to
        int promotedPiece{QUEEN};
        
        if(flag == PROMOTE_ROOK || flag == PROMOTE_ROOK_CAPTURE) 
        {
            promotedPiece = ROOK;
        }

        else if(flag == PROMOTE_BISHOP || flag == PROMOTE_BISHOP_CAPTURE) 
        {
            promotedPiece = BISHOP;
        }

        else if(flag == PROMOTE_KNIGHT || flag == PROMOTE_KNIGHT_CAPTURE) 
        {
            promotedPiece = KNIGHT;
        }

        // Place the new piece
        set_bit(bitboards[side][promotedPiece], target);
    }

    //Update En Passant state for the next turn
    if(flag == DOUBLE_PUSH)
    {
        enPassantSquare = (side == WHITE) ? target - 8 : target + 8;
    }

    else
    {
        enPassantSquare = -1; // Reset if the move wasn't a double push
    }

    // 7. Switch turns and rebuild occupancy maps
    turn = (side == WHITE) ? BLACK : WHITE;
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