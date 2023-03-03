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

}

#endif