#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.h"
#include "Gamestate.h"
#include "Movement.h"

using namespace std;
using namespace caveofprogramming;


int main() {
 
	// initialization
	Screen screen;
	if(screen.init()==false){
		cout<<"Error initalising SDL."<<endl;
		return 1;
	}
	Gamestate gamestate;
	// TODO: pointer to gamestate
	// Gamestate *pGamestate = &gamestate;
	if(gamestate.init()==false){
		cout<<"Error initalising gamestate."<<endl;
		return 1;
	}
	string board;
	board = gamestate.boardtoFEN();

	int MoveSelected[2][2]={NULL}; 
	bool StartMove =true;
	bool EndMove = false;
	int mx;
	int my;
	int square = screen.SCREEN_WIDTH/8;
	int row;
	int columm;
	SDL_Event e;

	screen.update(board);

	// game loop
	bool QUIT = false;
	while (!QUIT) {

		
		
		while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT:
					QUIT=true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&mx,&my);
					row = mx/square;
					columm = my/square;
					if(StartMove){
						MoveSelected[0][0]= row;
						MoveSelected[0][1]= columm;
						StartMove = false;
						EndMove = true;
						
					}
					else{
						MoveSelected[1][0]= row;
						MoveSelected[1][1]= columm;
						StartMove = true;
						EndMove = false;


						// initialize move
						Move move(gamestate.m_temp_board, MoveSelected[0][0], MoveSelected[1][0], MoveSelected[0][1], MoveSelected[1][1]);
						makeMove(gamestate.m_temp_board, move);
						cout<<endl;

						board = gamestate.boardtoFEN();
						screen.update(board);
						cout<<board<<endl;
						int rows=8;
						for (int i = 0; i < rows; i++) {
							for (int j = 0; j < 8; j++) {
								std::cout << gamestate.m_temp_board[i][j] << " ";
							}
							std::cout << std::endl;
    }
						
					}

			}
		}
		
		SDL_Delay(floor(32.0f));
	}

	screen.close();

	return 0;
}