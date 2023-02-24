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


	screen.update(board);
	// TODO: event driven
	while (true) {
		if(screen.processEvents()==false){
			break;
		}
	}

	screen.close();

	return 0;
}