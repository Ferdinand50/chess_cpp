#include "Screen.h"

namespace caveofprogramming{


Screen::Screen() :
    m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer(NULL) {
}



bool Screen::init(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL init failed." << endl;
		return false;
	}

	m_window = SDL_CreateWindow("Chess",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_WIDTH, SDL_WINDOW_SHOWN);


	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
							SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_WIDTH);

	if(m_renderer == NULL) {
		cout << "Could not create renderer" <<endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if(m_texture == NULL) {
		cout << "Could not create texture" <<endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer = new Uint32[SCREEN_WIDTH*SCREEN_WIDTH]; 

	memset(m_buffer, 255, SCREEN_WIDTH*SCREEN_WIDTH*sizeof(Uint32));

	SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH*sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
	SDL_RenderPresent(m_renderer);

    return true;
}

bool Screen::processEvents(){
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}


void Screen::draw_board(){
    //draw white board as foundation
    memset(m_buffer, 50, SCREEN_WIDTH*SCREEN_WIDTH*sizeof(Uint32));

	SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH*sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
	SDL_RenderPresent(m_renderer);

    // draw black squares
    SDL_Rect rect;
    rect.w = SCREEN_WIDTH/8;
    rect.h = SCREEN_WIDTH/8;

    int startPos = 0;
    for(int y=0; y<8;y++){
        for (int x = startPos; x<8; x+=2){
            rect.x = x*SCREEN_WIDTH/8;
            rect.y = y*SCREEN_WIDTH/8;
            SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(m_renderer,&rect);
        }
        startPos = 1- startPos;    
    }

    SDL_RenderPresent(m_renderer); 
}

void Screen::draw_pieces(){
    // quit image! 
    // load images in init
    SDL_Surface * image;

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        
    }
    image = IMG_Load("src/images/wK.png");


    m_texture = SDL_CreateTextureFromSurface(m_renderer, image);
    SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
    SDL_RenderPresent(m_renderer); 

}


void Screen::update(){
    draw_board();
    draw_pieces();

    
}

void Screen::close(){
	delete [] m_buffer;
    	
    IMG_Quit();
    // SDL_FreeSurface(m_image);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}


}