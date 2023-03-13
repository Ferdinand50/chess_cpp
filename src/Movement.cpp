#include "Movement.h"


namespace caveofprogramming{

const unsigned long long not_a_file = 18374403900871474942ULL;
const unsigned long long not_h_file = 9187201950435737471ULL;
const unsigned long long not_hg_file = 4557430888798830399ULL;
const unsigned long long not_ab_file = 18229723555195321596ULL;


// use pointer
void makeMove(unsigned long long m_bitboards[12], Move move){
    // //move piece to new square
    set_bit(m_bitboards[move.m_pieceMoved],move.m_end_square);

    //remove piece of start square
    pop_bit(m_bitboards[move.m_pieceMoved],move.m_start_square); 

    // //remove piece of end square if captured
    if(move.m_pieceTaken!=13){
        pop_bit(m_bitboards[move.m_pieceTaken],move.m_end_square);
    }
}


unsigned long long mask_pawn_attacks(int side, int square){

    //piece bitboard
    unsigned long long bitboard = 0ULL;

    //result attacks bitboard
    unsigned long long attacks = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    //white pawns
    if(!side){
        if((bitboard >>7) & not_a_file) attacks |= (bitboard <<7);
        if((bitboard >>9) & not_h_file) attacks |= (bitboard <<9);
    }

    //black pawns
    else{
        if((bitboard <<7) & not_h_file) attacks |= (bitboard <<7);
        if((bitboard <<9) & not_a_file) attacks |= (bitboard <<9);
    }

    return attacks;

}

// init leaper pieces attacks, it should return the pawn_attacks or use a pointer
// or move attack tables to movement!!!
void init_leapers_attacks(unsigned long long pawn_attacks[2][64]){
    //loop of board
    for(int square=0;square<64;square++){
        pawn_attacks[white][square]=mask_pawn_attacks(white, square);
        pawn_attacks[black][square]=mask_pawn_attacks(black, square);
    }
}

unsigned long long mask_knight_attacks(int square){

    //piece bitboard
    unsigned long long bitboard = 0ULL;

    //result attacks bitboard
    unsigned long long attacks = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    //generate knight attacks
   if((bitboard>>17)&not_h_file) attacks |= (bitboard>>17);
   if((bitboard>>15)&not_a_file) attacks |= (bitboard>>15);
   if((bitboard>>10)&not_hg_file) attacks |= (bitboard>>10);
   if((bitboard>>6)&not_ab_file) attacks |= (bitboard>>6);

   if((bitboard<<17)&not_a_file) attacks |= (bitboard<<17);
   if((bitboard<<15)&not_h_file) attacks |= (bitboard<<15);
   if((bitboard<<10)&not_ab_file) attacks |= (bitboard<<10);
   if((bitboard<<6)&not_hg_file) attacks |= (bitboard<<6);

}


unsigned long long mask_king_attacks(int square){

    //piece bitboard
    unsigned long long bitboard = 0ULL;

    //result attacks bitboard
    unsigned long long attacks = 0ULL;

    //set piece on board
    set_bit(bitboard, square);

    //generate king attacks
   if(bitboard>>8) attacks |= (bitboard>>8);
   if((bitboard>>9)&not_h_file) attacks |= (bitboard>>9);
   if((bitboard>>7)&not_a_file) attacks |= (bitboard>>7);
   if((bitboard>>1)&not_h_file) attacks |= (bitboard>>1);

   if(bitboard<<8) attacks |= (bitboard<<8);
   if((bitboard<<9)&not_a_file) attacks |= (bitboard<<9);
   if((bitboard<<7)&not_h_file) attacks |= (bitboard<<7);
   if((bitboard<<1)&not_a_file) attacks |= (bitboard<<1);

}

unsigned long long mask_bishop_attacks(int square){

    unsigned long long attacks = 0ULL;

    // init ranks and files
    int r, f;

    //init target rank and files
    int tr = square/8;
    int tf = square%8;

    //mask relevant bishop occupancy bits
    for(r=tr +1, f=tf+1; r<=6&&f<=6;r++,f++) attacks |=(1ULL<<(r*8+f));
    for(r=tr -1, f=tf+1; r>=1&&f<=6;r--,f++) attacks |=(1ULL<<(r*8+f));
    for(r=tr +1, f=tf-1; r<=6&&f>=1;r++,f--) attacks |=(1ULL<<(r*8+f));
    for(r=tr -1, f=tf-1; r>=1&&f>=1;r--,f--) attacks |=(1ULL<<(r*8+f));

    return attacks;
}

//generate bishop attacks on the fly 
unsigned long long bishop_attacks_on_the_fly(int square, unsigned long long block){

    unsigned long long attacks = 0ULL;

    // init ranks and files
    int r, f;

    //init target rank and files
    int tr = square/8;
    int tf = square%8;

    //generate bishop attacks, blocks for enemy pickes 
    for(r=tr +1, f=tf+1; r<=6&&f<=7;r++,f++) {
        attacks |=(1ULL<<(r*8+f));
        if((1ULL<<(r*8+f)) & block) break;
    }
    for(r=tr -1, f=tf+1; r>=1&&f<=0;r--,f++) {
        attacks |=(1ULL<<(r*8+f));
        if((1ULL<<(r*8+f))& block) break;
    }
    for(r=tr +1, f=tf-1; r<=6&&f>=7;r++,f--) {
        attacks |=(1ULL<<(r*8+f));
        if((1ULL<<(r*8+f)) & block) break;
    }
    for(r=tr -1, f=tf-1; r>=1&&f>=0;r--,f--) {
        attacks |=(1ULL<<(r*8+f));
        if((1ULL<<(r*8+f)) & block) break;
    }

    return attacks;
}

unsigned long long mask_rook_attacks(int square){

    unsigned long long attacks = 0ULL;

    // init ranks and files
    int r, f;

    //init target rank and files
    int tr = square/8;
    int tf = square%8;

    //mask relevant rook occupancy bits
    //down
    for(r=tr+1;r<=6;r++) attacks|=(1ULL << (r*8 + tf));
    //up
    for(r=tr-1;r>=6;r--) attacks|=(1ULL << (r*8 + tf));
    //right
    for(f=tf+1;f<=6;f++) attacks|=(1ULL << (tr*8 + f));
    //left
    for(f=tf-1;f>=6;f--) attacks|=(1ULL << (tr*8 + f));

    return attacks;
}
//generate rook attacks on the fly
unsigned long long rook_attack_on_the_fly(int square, unsigned long long block){

    unsigned long long attacks = 0ULL;

    // init ranks and files
    int r, f;

    //init target rank and files
    int tr = square/8;
    int tf = square%8;

    //generate rook attacks
    //down
    for(r=tr+1;r<=7;r++) {
        attacks|=(1ULL << (r*8 + tf));
        if((1ULL << (r*8 + tf)) & block) break;
    }
    //up
    for(r=tr-1;r>=0;r--) {
        attacks|=(1ULL << (r*8 + tf));
        if((1ULL << (r*8 + tf)) & block) break;
    }
    //right
    for(f=tf+1;f<=7;f++) {
        attacks|=(1ULL << (tr*8 + f));
        if((1ULL << (tr*8 + f)) & block) break;
    }
    //left
    for(f=tf-1;f>=0;f--) {
        attacks|=(1ULL << (tr*8 + f));
        if((1ULL << (tr*8 + f)) & block) break;
    }

    return attacks;
}

//helper functions

//count bits within a bitboard
static inline int count_bits(unsigned long long bitboard){

    //bit counter
    int count = 0;

    // consecutively reset least significant 1st bit
    while(bitboard){
        count ++;
        //reset least significant 1st bit
        bitboard &= bitboard-1;
    }

    //return bit count
    return count;
}



// Move class 

// 0r 1n 2b 3q 4k 5p 6R 7N 8B 9Q 10K 11P 
Move::Move(unsigned long long m_bitboards[12], int row_start, int row_end, int columm_start, int columm_end){
    m_start_square=columm_start*8 +row_start;
    m_end_square=columm_end*8 +row_end;

    //if m_pieceTaken stay 13 then the no piece is taken
    m_pieceTaken = 13;

    //TODO: make this more efficent (does not to check both colors)
    // get the index i for pieces of starting and ending position
    for(int i=0; i<12;i++){
        if(get_bit(m_bitboards[i],m_start_square)){
            m_pieceMoved = i;
        }
        if(get_bit(m_bitboards[i],m_end_square)){
            m_pieceTaken = i; 
        }
    }    
}





void Move::close(){

}

}