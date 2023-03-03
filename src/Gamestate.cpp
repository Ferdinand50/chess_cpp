#include "Gamestate.h"


namespace caveofprogramming {

Gamestate::Gamestate() :
    m_pawn_attacks{NULL},m_bitboards{NULL}{
}

// "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
bool Gamestate::init(){
    //init bitboards
    //black rooks
    set_bit(m_bitboards[0],a8);
    set_bit(m_bitboards[0],h8);
    //black knights
    set_bit(m_bitboards[1],b8);
    set_bit(m_bitboards[1],g8);
    //black bishops
    set_bit(m_bitboards[2],c8);
    set_bit(m_bitboards[2],f8);
    //black queen
    set_bit(m_bitboards[3],d8);
    //black king
    set_bit(m_bitboards[4],e8);
    //black pawns
    set_bit(m_bitboards[5],a7);
    set_bit(m_bitboards[5],b7);
    set_bit(m_bitboards[5],c7);
    set_bit(m_bitboards[5],d7);
    set_bit(m_bitboards[5],e7);
    set_bit(m_bitboards[5],f7);
    set_bit(m_bitboards[5],g7);
    set_bit(m_bitboards[5],h7);

    //white rooks
    set_bit(m_bitboards[6],a1);
    set_bit(m_bitboards[6],h1);
    //white knight
    set_bit(m_bitboards[7],b1);
    set_bit(m_bitboards[7],g1);
    //white bishops
    set_bit(m_bitboards[8],c1);
    set_bit(m_bitboards[8],f1);
    //white queen
    set_bit(m_bitboards[9],d1);
    //white king
    set_bit(m_bitboards[10],e1);
    //white pawns
    set_bit(m_bitboards[11],a2);
    set_bit(m_bitboards[11],b2);
    set_bit(m_bitboards[11],c2);
    set_bit(m_bitboards[11],d2);
    set_bit(m_bitboards[11],e2);
    set_bit(m_bitboards[11],f2);
    set_bit(m_bitboards[11],g2);
    set_bit(m_bitboards[11],h2);

    return true;
}


 
void Gamestate::printBitboard(unsigned long long bitboard){
    printf("\n");
    for(int rank=0; rank<8;rank++){
        for(int file=0; file<8;file++){
            int square=rank*8 +file;
            if(!file)
                printf("  %d", 8-rank);

            // print bit state either 1 or 0
            printf(" %d", get_bit(bitboard,square)?1:0);
        }
        printf("\n");
    }
    // print board files
    printf("\n    a b c d e f g h\n\n");
    //print bitboard as unsigned decial number
    printf("    Bitboard: %llud\n", bitboard);
       
}




void Gamestate::close(){

}

}