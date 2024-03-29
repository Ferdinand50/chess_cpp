#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <iostream>
using namespace std;

namespace caveofprogramming {

class Gamestate {
public:
    unsigned long long m_bitboards[12];
    unsigned long long test_bitboards[12];
    //[side(color)],[square]
    unsigned long long m_pawn_attacks[2][64];
    unsigned long long m_knight_attacks[64];
    unsigned long long m_king_attacks[64];
    unsigned long long m_bishop_attacks[64];
private:
    
    

public:
    Gamestate();
    bool init();
    void printBitboard(unsigned long long bitboard);    
    void close();
};



// set/get/pop bit macros
#define set_bit(bitboard,square) bitboard |= (1ULL<<square)
#define get_bit(bitboard,square) (bitboard &(1ULL<<square))
#define pop_bit(bitboard,square) (get_bit(bitboard, square)? bitboard ^= (1ULL<<square):0)

//board sqaures
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

// white is 0, black is 1
enum {white, black};

//bishop and rook
enum {rook, bishop};



}

#endif