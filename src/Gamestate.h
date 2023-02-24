#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <iostream>
using namespace std;

namespace caveofprogramming {

class Gamestate {
public:
    unsigned long long m_bitmap[12];
private:
    char m_temp_board[8][8];
    

public:
    Gamestate();
    bool init();
    string boardtoFEN();
    void close();
};


}

#endif