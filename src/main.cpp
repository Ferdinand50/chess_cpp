#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.h"
#include "Gamestate.h"
using namespace std;
using namespace caveofprogramming;


int main() {
 

	Screen screen;
	if(screen.init()==false){
		cout<<"Error initalising SDL."<<endl;
		return 1;
	}

	Gamestate gamestate;
	if(gamestate.init()==false){
		cout<<"Error initalising gamestate."<<endl;
		return 1;
	}

	string board;
	board = gamestate.boardtoFEN();


	
	// TODO: event driven
	while (true) {

		screen.update(board);
		if(screen.processEvents()==false){
			break;
		}
		
		SDL_Delay(floor(32.0f));
	}

	screen.close();

	return 0;
}