#include "Gamestate.h"


namespace caveofprogramming {

Gamestate::Gamestate() :
    m_temp_board       {{"r","n","b","q","k","b","n","r"},
                        {"p","p","p","p","p","p","p","p"},
                        {"e","e","e","e","e","e","e","e"},
                        {"e","e","e","e","e","e","e","e"},
                        {"e","e","e","e","e","e","e","e"},
                        {"e","e","e","e","e","e","e","e"},
                        {"P","P","P","P","P","P","P","P"},
                        {"R","N","B","Q","K","B","N","R"}} ,m_bitboards{NULL}, 
    m_test_bitboard(0ULL), m_pawn_attacks{NULL}{
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

string Gamestate::boardtoFEN(){
    string FEN ="";
    int number_counter = 0;
    for(int i=0; i<8; i++){
        for(int j=0; j<8;j++){
           if(*m_temp_board[i][j]=='e'){
            number_counter = number_counter + 1;
            if(number_counter>0){
                FEN.push_back(char(number_counter+48));
            }
           }

           else{
            FEN.push_back(*m_temp_board[i][j]);
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


string Gamestate::bitboardtoFEN(){
    string FEN ="";

    return FEN;
}


 



void Gamestate::printBitboard(unsigned long long bitboard[12]){
    printf("\n");

    for(int i=0; i<12;i++){
        for(int rank=0; rank<8;rank++){
            for(int file=0; file<8;file++){
                int square=rank*8 +file;

                if(!file)
                    printf("  %d", 8-rank);

                // print bit state either 1 or 0
                printf(" %d", get_bit(bitboard[i],square)?1:0);
                
            }
            printf("\n");
            
        }
        // print board files
        printf("\n    a b c d e f g h\n\n");
        //print bitboard as unsigned decial number
        printf("    Bitboard: %llud\n", bitboard);
    }   
}




void Gamestate::close(){

}

}