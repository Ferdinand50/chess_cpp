#include "Gamestate.h"


namespace caveofprogramming {

Gamestate::Gamestate() :
    m_temp_board       {{'r','n','b','q','k','b','n','r'},
                        {'p','p','p','p','p','p','p','p'},
                        {'e','e','e','e','e','e','e','e'},
                        {'e','e','e','e','e','e','e','e'},
                        {'e','e','e','e','e','e','e','e'},
                        {'e','e','e','e','e','e','e','e'},
                        {'P','P','P','P','P','P','P','P'},
                        {'R','N','B','Q','K','B','N','R'}} ,m_bitmap{NULL}{
}

// "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
bool Gamestate::init(){
    // m_bitmap[0]=0000000000000000ULL;

    // m_temp_board[8][8]={{'r','n','b','q','k','b','n','r'},
    //                     {'p','p','p','p','p','p','p','p'},
    //                     {'e','e','e','e','e','e','e','e'},
    //                     {'e','e','e','e','e','e','e','e'},
    //                     {'e','e','e','e','e','e','e','e'},
    //                     {'e','e','e','e','e','e','e','e'},
    //                     {'P','P','P','P','P','P','P','P'},
    //                     {'R','N','B','Q','K','B','N','R'}};

    return true;
}

string Gamestate::boardtoFEN(){
    string FEN ="";
    int number_counter = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8;j++){
           if(m_temp_board[i][j]=='e'){
            number_counter = number_counter + 1;
            if(number_counter>0){
                FEN.push_back(char(number_counter+48));
            }
           }

           else{
            FEN.push_back(m_temp_board[i][j]);
            number_counter = 0;
           }
        }
        if(i<7){
            FEN.push_back('/');
        }
        number_counter = 0;
    }
    bool previous_number = false;
    for(int i=0; i<FEN.length();i++){
        if(isdigit(FEN[i])){
            if(previous_number==true){
                previous_number = true;
                 FEN.erase(i-1, 1);
                 i = i-1;
            }
            else {
                previous_number = true;
            }
        }
        else{
            previous_number = false;
        }
    }
    return FEN;
}

void Gamestate::close(){

}

}