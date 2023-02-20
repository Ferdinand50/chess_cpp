#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

int main() {

	const int SCREEN_WIDTH = 1600;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL init failed." << endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Chess",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_WIDTH, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Quit();
		return 2;
	}

	bool quit = false;

	SDL_Event event;

	while (!quit) {


		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}