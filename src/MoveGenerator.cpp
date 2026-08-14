#include "MoveGenerator.hpp"
#include "BitUtils.hpp"
#include "Board.hpp"

using u64 = uint64_t;

MoveGenerator::MoveGenerator() 
{
    int dx_knight[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy_knight[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    generateLeaperMoves(knightAttacks, dx_knight, dy_knight);

    int dx_king[8] = {1, 1, 1, 0, 0, -1, -1, -1};
    int dy_king[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    generateLeaperMoves(kingAttacks, dx_king, dy_king);

    initPawnAttacks();
    initRays();
}

void MoveGenerator::generateLeaperMoves(u64 table[64], const int dx[8], const int dy[8])
{
    for(int square{}; square < 64; ++square) 
    {
        table[square] = 0;

        int row{square/8};
        int col{square % 8};

        for(int i{}; i < 8; ++i) 
        {   
            int nrow{row + dx[i]};
            int ncol{col + dy[i]};

            if(nrow >= 0 && nrow <= 7 && ncol >= 0 && ncol <= 7) 
            {
                int targetSquare{nrow * 8 + ncol};
                set_bit(table[square], targetSquare);
            }
        }
    }
}

void MoveGenerator::initPawnAttacks() 
{
    for(int square{}; square < 64; ++square) 
    {
        pawnAttacks[0][square] = 0; 
        pawnAttacks[1][square] = 0; 

        int row{square/8};
        int col{square % 8};

        //white pawns only move up
        if(row < 7) 
        {
            //left attack
            if(col > 0) 
                set_bit(pawnAttacks[0][square], (row + 1) * 8 + (col - 1));

            //right attack
            if(col < 7) 
                set_bit(pawnAttacks[0][square], (row + 1) * 8 + (col + 1));
        }

        //black pawns only move down
        if(row > 0) 
        {
            //left attack
            if(col > 0) 
                set_bit(pawnAttacks[1][square], (row - 1) * 8 + (col - 1));

            //right attack
            if(col < 7) 
                set_bit(pawnAttacks[1][square], (row - 1) * 8 + (col + 1));
        }
    }
}

void MoveGenerator::initRays() 
{
    int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1}; 
    int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1}; 

    for(int square{}; square < 64; ++square) 
    {
        int row{square/8};
        int col{square % 8};

        for(int dir{}; dir < 8; ++dir) 
        {
            rays[dir][square] = 0;

            int r{row + dx[dir]};
            int c{col + dy[dir]};

            while(r >= 0 && r <= 7 && c >= 0 && c <= 7) 
            {
                int targetSquare{r * 8 + c};
                set_bit(rays[dir][square], targetSquare);
                    
                r += dx[dir];
                c += dy[dir];
            }
        }
    }
}

u64 MoveGenerator::getRookAttacks(int square, u64 occupied) const 
{
    u64 attacks{};
    u64 ray{}, blockers{};

    ray = rays[NORTH][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[NORTH][get_lsb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[EAST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[EAST][get_lsb(blockers)]);
    
    else 
        attacks |= ray;

    ray = rays[SOUTH][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[SOUTH][get_msb(blockers)]);
    
    else 
        attacks |= ray;

    ray = rays[WEST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[WEST][get_msb(blockers)]);

    else 
        attacks |= ray;

    return attacks;
}

u64 MoveGenerator::getBishopAttacks(int square, u64 occupied) const 
{
    u64 attacks{};
    u64 ray, blockers;

    ray = rays[NORTH_EAST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[NORTH_EAST][get_lsb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[NORTH_WEST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[NORTH_WEST][get_lsb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[SOUTH_EAST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[SOUTH_EAST][get_msb(blockers)]);

    else 
        attacks |= ray;

    ray = rays[SOUTH_WEST][square];
    blockers = ray & occupied;

    if(blockers) 
        attacks |= (ray ^ rays[SOUTH_WEST][get_msb(blockers)]);

    else 
        attacks |= ray;

    return attacks;
}

//Queen is Bishop and rook combined
u64 MoveGenerator::getQueenAttacks(int square, u64 occupied) const 
{
    return getRookAttacks(square, occupied) | getBishopAttacks(square, occupied);
}

u64 MoveGenerator::getPawnAttacks(int color, int square) const 
{
    return pawnAttacks[color][square];
}

u64 MoveGenerator::getKnightAttacks(int square) const 
{
    return knightAttacks[square];
}

u64 MoveGenerator::getKingAttacks(int square) const 
{
    return kingAttacks[square];
}

u64 MoveGenerator::getRay(Direction dir, int square) const 
{
    return rays[dir][square];
}

void MoveGenerator::generateMoves(const Board& board, MoveList& moveList) const 
{
    int side{board.getSide()};
    int enemySide{(side == WHITE) ? BLACK : WHITE};

    u64 friendlyOccupancy{board.getOccupancy(side)};
    u64 enemyOccupancy{board.getOccupancy(enemySide)};
    u64 globalOccupancy{board.getOccupancy(BOTH)}; 

    // --- PAWNS ---
    if(side == WHITE) 
    {
        u64 pawns{board.getPieceBitboard(WHITE, PAWN)};
        
        // 1. Single Pushes (Shift Up 8 squares, must be empty)
        u64 singlePushes{(pawns << 8) & ~globalOccupancy};
        u64 pushes{singlePushes};
        
        while(pushes) 
        {
            int targetSquare{get_lsb(pushes)};
            int sourceSquare{targetSquare - 8};
            
            //If it reaches Rank 8 (squares 56-63), it's a promotion
            if(targetSquare >= 56) 
            {
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_QUEEN));
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_ROOK));
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_BISHOP));
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_KNIGHT));
            } 

            else 
            {
                moveList.add(encodeMove(sourceSquare, targetSquare, QUIET));
            }

            pushes &= (pushes - 1);
        }
        
        // 2. Double Pushes 
        // Single pushes onto Row 3 (0x0000000000FF0000ULL), shifted up 8 MORE squares, must be empty
        u64 doublePushes{((singlePushes & 0x0000000000FF0000ULL) << 8) & ~globalOccupancy};
        
        while(doublePushes) 
        {
            int targetSquare{get_lsb(doublePushes)};
            int sourceSquare{targetSquare - 16};
            moveList.add(encodeMove(sourceSquare, targetSquare, DOUBLE_PUSH));
            doublePushes &= (doublePushes - 1);
        }
        
        // 3. (Diagonal captures)

        u64 validTargets{enemyOccupancy};
        u64 attackers{pawns};
        while(attackers) 
        {
            int sourceSquare{get_lsb(attackers)};
            u64 attacks{getPawnAttacks(WHITE, sourceSquare) & validTargets};
            
            while(attacks) 
            {
                int targetSquare{get_lsb(attacks)};
                
                if(targetSquare == board.enPassantSquare)
                {
                    moveList.add(encodeMove(sourceSquare, targetSquare, EN_PASSANT));
                }
                
                else if(targetSquare >= 56) 
                { 
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_QUEEN_CAPTURE));
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_ROOK_CAPTURE));
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_BISHOP_CAPTURE));
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_KNIGHT_CAPTURE));
                } 

                else 
                {
                    moveList.add(encodeMove(sourceSquare, targetSquare, CAPTURE));
                }

                attacks &= (attacks - 1);
            }
            
            attackers &= (attackers - 1);
        }
    } 

    else 
    {
        u64 pawns{board.getPieceBitboard(BLACK, PAWN)};
        
        //1. Single Pushes (Shift Down 8 squares, must be empty)
        u64 singlePushes{(pawns >> 8) & ~globalOccupancy};
        u64 pushes{singlePushes};
        
        while(pushes) 
        {
            int targetSquare{get_lsb(pushes)};
            int sourceSquare{targetSquare + 8};
            
            // If it reaches Rank 1 (squares 0-7), it's a promotion
            if(targetSquare <= 7) 
            {
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_QUEEN));
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_ROOK));
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_BISHOP));
                moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_KNIGHT));
            } 

            else 
            {
                moveList.add(encodeMove(sourceSquare, targetSquare, QUIET));
            }

            pushes &= (pushes - 1);
        }
        
        // 2. Double Pushes 
        // Single pushes onto Rank 6 (0x0000FF0000000000ULL), shifted down 8 MORE squares, must be empty
        u64 doublePushes{((singlePushes & 0x0000FF0000000000ULL) >> 8) & ~globalOccupancy};
        
        while(doublePushes) 
        {
            int targetSquare{get_lsb(doublePushes)};
            int sourceSquare{targetSquare + 16};
            moveList.add(encodeMove(sourceSquare, targetSquare, DOUBLE_PUSH));
            doublePushes &= (doublePushes - 1);
        }
        
        // 3. Pawn Attacks (Diagonal captures)
        u64 attackers{pawns};

        while(attackers) 
        {
            int sourceSquare{get_lsb(attackers)};
            u64 attacks{getPawnAttacks(BLACK, sourceSquare) & enemyOccupancy};
            
            while(attacks) 
            {
                int targetSquare{get_lsb(attacks)};
                
                if (targetSquare <= 7) 
                { 
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_QUEEN_CAPTURE));
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_ROOK_CAPTURE));
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_BISHOP_CAPTURE));
                    moveList.add(encodeMove(sourceSquare, targetSquare, PROMOTE_KNIGHT_CAPTURE));
                } 

                else 
                {
                    moveList.add(encodeMove(sourceSquare, targetSquare, CAPTURE));
                }
                attacks &= (attacks - 1);
            }

            attackers &= (attackers - 1);
        }
    }
    
    //1.KNIGHTS
    u64 knights{board.getPieceBitboard(side, KNIGHT)};

    while(knights) 
    {
        int sourceSquare{get_lsb(knights)};
        u64 attacks{getKnightAttacks(sourceSquare) & ~friendlyOccupancy};

        while(attacks) 
        {
            int targetSquare{get_lsb(attacks)};
            int flag{get_bit(enemyOccupancy, targetSquare) ? CAPTURE : QUIET};
            moveList.add(encodeMove(sourceSquare, targetSquare, flag));
            attacks &= (attacks - 1); 
        }

        knights &= (knights - 1); 
    }

    //2.KINGS
    u64 kings{board.getPieceBitboard(side, KING)};
    
    while(kings) 
    {
        int sourceSquare{get_lsb(kings)};
        u64 attacks{getKingAttacks(sourceSquare) & ~friendlyOccupancy};

        while(attacks) 
        {
            int targetSquare{get_lsb(attacks)};
            int flag{get_bit(enemyOccupancy, targetSquare) ? CAPTURE : QUIET};
            moveList.add(encodeMove(sourceSquare, targetSquare, flag));
            attacks &= (attacks - 1); 
        }

        kings &= (kings - 1); 
    }

    //3. BISHOPS
    u64 bishops{board.getPieceBitboard(side, BISHOP)};

    while(bishops) 
    {
        int sourceSquare{get_lsb(bishops)};
        u64 attacks{getBishopAttacks(sourceSquare, globalOccupancy) & ~friendlyOccupancy};

        while(attacks) 
        {
            int targetSquare{get_lsb(attacks)};
            int flag{get_bit(enemyOccupancy, targetSquare) ? CAPTURE : QUIET};
            moveList.add(encodeMove(sourceSquare, targetSquare, flag));
            attacks &= (attacks - 1); 
        }

        bishops &= (bishops - 1); 
    }

    //4. ROOKS
    u64 rooks{board.getPieceBitboard(side, ROOK)};

    while(rooks) 
    {
        int sourceSquare{get_lsb(rooks)};
        u64 attacks{getRookAttacks(sourceSquare, globalOccupancy) & ~friendlyOccupancy};

        while(attacks) 
        {
            int targetSquare{get_lsb(attacks)};
            int flag{get_bit(enemyOccupancy, targetSquare) ? CAPTURE : QUIET};
            moveList.add(encodeMove(sourceSquare, targetSquare, flag));
            attacks &= (attacks - 1); 
        }

        rooks &= (rooks - 1); 
    }

    //5. QUEENS
    u64 queens{board.getPieceBitboard(side, QUEEN)};

    while(queens) 
    {
        int sourceSquare{get_lsb(queens)};
        u64 attacks{getQueenAttacks(sourceSquare, globalOccupancy) & ~friendlyOccupancy};

        while(attacks) 
        {
            int targetSquare = get_lsb(attacks);
            int flag{get_bit(enemyOccupancy, targetSquare) ? CAPTURE : QUIET};
            moveList.add(encodeMove(sourceSquare, targetSquare, flag));
            attacks &= (attacks - 1); 
        }

        queens &= (queens - 1); 
    }
}