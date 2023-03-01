#include "Pieces.h"
#include "Gamestate.h"


namespace caveofprogramming {



unsigned long long mask_pawn_attacks(int square, int side){

    unsigned long long attacks =0ULL;
    unsigned long long bitboard =0ULL;
    set_bit(bitboard,square);

    // white pawns
    if(!side){

    }
    //black pawns
    else{

    }

    return attacks;
}


}