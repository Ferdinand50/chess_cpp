#ifndef MOVEMENT_H_
#define Movement_H_

#include <iostream>
#include "Gamestate.h"
using namespace std;

namespace caveofprogramming {

class Move{
public:
    // rewrite piece type into bit
    int m_pieceMoved;
    int m_pieceTaken;
    int m_start_square;
    int m_end_square;

    // add moveID and isCatleMove and is enpasstMove
private:
    
    

public:
    Move(unsigned long long m_bitboards[12], int row_start, int row_end, int columm_start, int columm_end);
    void close();
};


void makeMove(unsigned long long m_bitboards[12], Move move);

unsigned long long mask_pawn_attacks(int square, int side);
unsigned long long mask_knight_attacks(int square);
unsigned long long mask_king_attacks(int square);
unsigned long long mask_bishop_attacks(int square);
unsigned long long mask_rook_attacks(int square);
unsigned long long bishop_attacks_on_the_fly(int square, unsigned long long block);
unsigned long long rook_attack_on_the_fly(int square, unsigned long long block);
static inline int count_bits(unsigned long long bitboard);
int return_piece_type(int MoveSelected[2], unsigned long long bitboard[12]);
}

#endif