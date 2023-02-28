#include "Movement.h"


namespace caveofprogramming{


void makeMove(char *board[8][8], Move move){
    board[move.m_columm_start][move.m_row_start] = "e";
    board[move.m_columm_end][move.m_row_end] = move.m_pieceMoved;


}

Move::Move(char *board[8][8], int row_start, int row_end, int columm_start, int columm_end){
    m_pieceMoved = board[columm_start][row_start];
    m_pieceTaken = board[columm_end][row_end];
    m_row_start=row_start;
    m_row_end=row_end;
    m_columm_start=columm_start;
    m_columm_end=columm_end;

}





void Move::close(){

}

}