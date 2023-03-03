#include "Movement.h"


namespace caveofprogramming{

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