#ifndef MOVEMENT_H_
#define Movement_H_

#include <iostream>
#include "Gamestate.h"
using namespace std;

namespace caveofprogramming {

class Move{
public:
    // rewrite piece type into bit
    char m_pieceMoved;
    char m_pieceTaken;
    int m_row_start;
    int m_row_end;
    int m_columm_start;
    int m_columm_end;
    // add moveID and isCatleMove and is enpasstMove
private:
    
    

public:
    Move(Gamestate gamestate, int row_start, int row_end, int columm_start, int columm_end);
    void close();
};


void makeMove(Gamestate gamestate, Move move);

}

#endif