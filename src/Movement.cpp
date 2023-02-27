#include "Movement.h"


namespace caveofprogramming{


void makeMove(Gamestate gamestate, Move move){
    gamestate.m_temp_board[move.m_row_start][move.m_columm_start] = 'e';
    gamestate.m_temp_board[move.m_row_end][move.m_columm_end] = move.m_pieceMoved;

}

Move::Move(Gamestate gamestate, int row_start, int row_end, int columm_start, int columm_end){
    m_pieceMoved = gamestate.m_temp_board[row_start][columm_start];
    m_pieceTaken = gamestate.m_temp_board[row_end][columm_end];
    m_row_start=row_start;
    m_row_end=row_end;
    m_columm_start=columm_start;
    m_columm_end=columm_end;
}




void Move::close(){

}

}