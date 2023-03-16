#include "Movement.h"


namespace caveofprogramming{

const unsigned long long not_a_file = 18374403900871474942ULL;
const unsigned long long not_h_file = 9187201950435737471ULL;
const unsigned long long not_hg_file = 4557430888798830399ULL;
const unsigned long long not_ab_file = 18229723555195321596ULL;

//relevent occupancy bit count for every square on board
const int bishop_relevant_bits[64]=  {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rook_relevant_bits[64]=  {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

// rook magic numbers
unsigned long long rook_magic_numbers[64] ={
0x2000380201000008ULL,
0x9002041009000030ULL,
0x1000430100100082ULL,
0x808008040002020ULL,
0x801a0105000424ULL,
0x12000018200000a0ULL,
0x2000020800220040ULL,
0x40801910d4004ULL,
0x1020210000040180ULL,
0x1915500080810013ULL,
0x10001024104152ULL,
0x8000020400881001ULL,
0xc0018c1000262001ULL,
0xa001000200060ULL,
0xc00000e00a000500ULL,
0x4050008210040800ULL,
0x25c080804200101ULL,
0x3200a40580200001ULL,
0x4000200008ULL,
0x8040000601381ULL,
0x30120000002000ULL,
0x1000082400000400ULL,
0x808c008214000ULL,
0x1000480000004c03ULL,
0x200000040000020aULL,
0x24a20400400010ULL,
0x800000005310000ULL,
0x10026001364808ULL,
0x8c02100001200ULL,
0x8048a000080000ULL,
0x2022188000040120ULL,
0x1800101200ULL,
0x1800501000088104ULL,
0x4800800002008202ULL,
0x20002949220ULL,
0x102180b0004121ULL,
0x500040000084080ULL,
0x7000000009018ULL,
0x1520040030002800ULL,
0x2000820300180020ULL,
0x11800049000200ULL,
0x4040812681000480ULL,
0x1c01c1020000ULL,
0x880208001804ULL,
0x2212000400480a00ULL,
0x8000100001200820ULL,
0x671080100040000ULL,
0x400302200d0000ULL,
0x2000000000060400ULL,
0x4090808148101ULL,
0x2040200200020ULL,
0x8000c001020c0001ULL,
0x800000110201010ULL,
0x400c802211420200ULL,
0x144a81020800026ULL,
0x4000001000d2000ULL,
0x1a10004004004ULL,
0xa09540042500000ULL,
0x540008008069ULL,
0x1080c804200ULL,
0xa000081241180380ULL,
0x800880000402445ULL,
0x8040035200202040ULL,
0x400080002440020ULL
};

//bishop magic numbers
unsigned long long bishop_magic_numbers[64] = {
0x8000900140840092ULL,
0x804840004c900ULL,
0x4018a4000100200ULL,
0x2008028800020000ULL,
0x4003108c18304c34ULL,
0x2c08401405280000ULL,
0x100780600010ULL,
0xc408004a001040ULL,
0x800420008018010ULL,
0x1800012898000018ULL,
0x62040981c0001032ULL,
0x102120030402100ULL,
0x10182840048180ULL,
0x50405800000840ULL,
0x4300085008ULL,
0x11008402150a0200ULL,
0x840011004044280ULL,
0x704840810202ULL,
0x8000020e080001ULL,
0x8808008200808401ULL,
0x44c20212800000ULL,
0x18000d090041800ULL,
0x10e020504211200ULL,
0x200021018440400ULL,
0xaa0001210064048ULL,
0x241102000008124ULL,
0x100002c12180204ULL,
0x880200102070ULL,
0x40200052008011ULL,
0x430000d0ULL,
0x8024c0005408060fULL,
0x400002000c50060ULL,
0x422008180c1020ULL,
0x2308102a00414400ULL,
0x2000082020004206ULL,
0x8004000c2024090ULL,
0x6006501801ULL,
0x88880004685010ULL,
0x10000802040003c0ULL,
0x1010430800024000ULL,
0x410041240190800ULL,
0x1804000b00810100ULL,
0x800002808000284ULL,
0x648041000ULL,
0x80010802081044ULL,
0x8080024009001042ULL,
0x3000dc020500020ULL,
0x80042000e00004ULL,
0x220802468032200ULL,
0x10858020080a0ULL,
0x2080604201818000ULL,
0x8002100214000ULL,
0x8040000821802000ULL,
0xa0001200000c020ULL,
0x100090004e800ULL,
0x28890000282040ULL,
0x40502920100000ULL,
0x8020293001200840ULL,
0x2605400040003000ULL,
0x2200002002800446ULL,
0x200806200a008ULL,
0x801400600042100ULL,
0x2900290080208400ULL,
0x5000020058ULL
};

const char *square_to_coordinates[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
};


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
    
    // init target rank & files
    int tr = square / 8;
    int tf = square % 8;
    
    // mask relevant rook occupancy bits
    for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
    for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));
    
    // return attack map
    return attacks;
}
//generate rook attacks on the fly
unsigned long long rook_attacks_on_the_fly(int square, unsigned long long block){

    unsigned long long attacks = 0ULL;

    // init ranks and files
    int r, f;
    
    // init target rank & files
    int tr = square / 8;
    int tf = square % 8;
    
    // generate rook attacks
    for (r = tr + 1; r <= 7; r++)
    {
        attacks |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) & block) break;
    }
    
    for (r = tr - 1; r >= 0; r--)
    {
        attacks |= (1ULL << (r * 8 + tf));
        if ((1ULL << (r * 8 + tf)) & block) break;
    }
    
    for (f = tf + 1; f <= 7; f++)
    {
        attacks |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) & block) break;
    }
    
    for (f = tf - 1; f >= 0; f--)
    {
        attacks |= (1ULL << (tr * 8 + f));
        if ((1ULL << (tr * 8 + f)) & block) break;
    }
    
    // return attack map
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

//get least significant 1st bit indexx
static inline int get_ls1b_index(unsigned long long bitboard){
    // make sure bitbord is not zero
    if(bitboard){
        //count trailing bits before LS1B
        return count_bits((bitboard & bitboard)-1);
    }
    else{
        //return illegal index
        return -1;
    }
}

//set occupancies
unsigned long long set_occupancy(int index, int bits_in_mask, unsigned long long attack_mask){

    // occupancy mask
    unsigned long long occupancy = 0ULL;

    //loop over the range of the bits within attack mask
    for (int count = 0; count < bits_in_mask; count++)
    {
        // get LS1B index of attacks mask
        int square = get_ls1b_index(attack_mask);
        
        // pop LS1B in attack map
        pop_bit(attack_mask, square);
        
        // make sure occupancy is on board
        if (index & (1 << count))
            // populate occupancy map
            occupancy |= (1ULL << square);
    }
    
    // return occupancy map
    return occupancy;
}

unsigned int random_state = 1804289383;

// generate 32-bit pseudo legal number
unsigned int get_random_U32_number(){
    // get current state
    unsigned int number = random_state;
    
    // XOR shift algorithm
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;
    
    // update random number state
    random_state = number;
    
    // return random number
    return number;

}

// generate 64-bit pseudo legal numbers
unsigned long long get_random_U64_number(){

    //define 4 random numbers
    unsigned long long n1, n2, n3, n4;
    
    // init random numbers slicing 16 bits from MS1B side
    n1 = (unsigned long long)(get_random_U32_number()) & 0xFFFF;
    n2 = (unsigned long long)(get_random_U32_number()) & 0xFFFF;
    n3 = (unsigned long long)(get_random_U32_number()) & 0xFFFF;
    n4 = (unsigned long long)(get_random_U32_number()) & 0xFFFF;
    
    // return random number
    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);

}

//generate magic number candidate
unsigned long long generate_magic_number(){
    return get_random_U64_number() & get_random_U64_number() & get_random_U64_number();
}

//return piece type in square
int return_piece_type(int MoveSelected[2], unsigned long long bitboards[12]){

    int square = MoveSelected[1]*8 +MoveSelected[0];
    int piece_type;
    for(int i=0; i<12;i++){
        if(get_bit(bitboards[i],square)) {
        piece_type = i;
        break;
        }
    }

    return piece_type;
}

/*************************************************************\
 =============================================================

                             Magics

 =============================================================
\*************************************************************/

// find appropriate magic number
unsigned long long find_magic_number(int square, int relevant_bits, int bishop)
{
    // init occupancies
    unsigned long long occupancies[4096];
    
    // init attack tables
    unsigned long long attacks[4096];
    
    // init used attacks
    unsigned long long used_attacks[4096];
    
    // init attack mask for a current piece
    unsigned long long attack_mask = bishop ? mask_bishop_attacks(square) : mask_rook_attacks(square);
    
    // init occupancy indicies
    int occupancy_indicies = 1 << relevant_bits;
    
    // loop over occupancy indicies
    for (int index = 0; index < occupancy_indicies; index++)
    {
        // init occupancies
        occupancies[index] = set_occupancy(index, relevant_bits, attack_mask);
        
        // init attacks
        attacks[index] = bishop ? bishop_attacks_on_the_fly(square, occupancies[index]) :
                                    rook_attacks_on_the_fly(square, occupancies[index]);
    }
    
    // test magic numbers loop
    for (int random_count = 0; random_count < 100000000; random_count++)
    {
        // generate magic number candidate
        unsigned long long magic_number = generate_magic_number();
        
        // skip inappropriate magic numbers
        if (count_bits((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;
        
        // init used attacks
        memset(used_attacks, 0ULL, sizeof(used_attacks));
        
        // init index & fail flag
        int index, fail;
        
        // test magic index loop
        for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++)
        {
            // init magic index
            int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));
            
            // if magic index works
            if (used_attacks[magic_index] == 0ULL)
                // init used attacks
                used_attacks[magic_index] = attacks[index];
            
            // otherwise
            else if (used_attacks[magic_index] != attacks[index])
                // magic index doesn't work
                fail = 1;
        }
        
        // if magic number works
        if (!fail)
            // return it
            return magic_number;
    }
    
    // if magic number doesn't work
    printf("  Magic number fails!\n");
    return 0ULL;
}

// init magic numbers
void init_magic_numbers()
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++){
        // init rook magic numbers
        rook_magic_numbers[square] = find_magic_number(square, rook_relevant_bits[square], rook);
        
    }
    // loop over 64 board squares
    for (int square = 0; square < 64; square++){
        // init bishop magic numbers
        bishop_magic_numbers[square] = find_magic_number(square, bishop_relevant_bits[square], bishop);
        // printf("0x%llxULL,\n",bishop_magic_numbers[square]);
    }
    

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