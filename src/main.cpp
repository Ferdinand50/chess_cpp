#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.h"
#include "Gamestate.h"
#include "Movement.h"
#include "Pieces.h"

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

	int MoveSelected[2][2]={NULL}; 
	bool StartMove =true;
	bool EndMove = false;
	int mx;
	int my;
	int square = screen.SCREEN_WIDTH/8;
	int row;
	int columm;
	SDL_Event e;

	// gamestate.printBitboard(gamestate.m_bitboards);

	screen.update(gamestate.m_bitboards);

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
						Move move(gamestate.m_bitboards, MoveSelected[0][0], MoveSelected[1][0], MoveSelected[0][1], MoveSelected[1][1]);
						makeMove(gamestate.m_bitboards, move);

						// gamestate.printBitboard(gamestate.m_bitboards[0]);
						// cout<<"piece moved: " << move.m_pieceMoved<<endl;
						// cout<<"piece taken: " << move.m_pieceTaken<<endl;
						

						screen.update(gamestate.m_bitboards);

						
					}

			}
		}
		
		SDL_Delay(floor(32.0f));
	}

	screen.close();

	return 0;
}