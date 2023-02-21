#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.h"
using namespace std;
using namespace caveofprogramming;

int main() {

	Screen screen;

	if(screen.init()==false){
		cout<<"Error initalising SDL."<<endl;
		return 1;
	}

	screen.update();

	// TODO: event driven
	while (true) {
		if(screen.processEvents()==false){
			break;
		}
	}

	screen.close();

	return 0;
}