#include "Screen.h"
#include <map>

namespace caveofprogramming{



Screen::Screen() :
    m_current_click{NULL},m_previous_click{NULL}, m_second_click(false),m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer(NULL),m_images{NULL}{
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

    //load Images
    m_images[0] = IMG_Load("src/images/bR.png");
    m_images[1] = IMG_Load("src/images/bN.png");
    m_images[2] = IMG_Load("src/images/bB.png");
    m_images[3] = IMG_Load("src/images/bQ.png");
    m_images[4] = IMG_Load("src/images/bK.png");
    m_images[5] = IMG_Load("src/images/bP.png");

    m_images[6] = IMG_Load("src/images/wR.png");
    m_images[7] = IMG_Load("src/images/wN.png");
    m_images[8] = IMG_Load("src/images/wB.png");
    m_images[9] = IMG_Load("src/images/wQ.png");
    m_images[10] = IMG_Load("src/images/wK.png");
    m_images[11] = IMG_Load("src/images/wP.png");

    return true;
}




void Screen::draw_board(){

int startPos = 0;
for (int y = 0; y < 8; y++) {       
    for (int x = startPos; x < 8; x+=2) {           
            SDL_Rect rect;
            rect.x = x * SCREEN_WIDTH/8;
            rect.y = y * SCREEN_WIDTH/8;
            rect.w = SCREEN_WIDTH/8;
            rect.h = SCREEN_WIDTH/8;
            SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
            SDL_RenderFillRect(m_renderer, &rect);              
    }
    startPos = 1 - startPos;
}

}



void Screen::draw_pieces(string board_state){

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        
    }

    SDL_Rect rect;
    rect.w = SCREEN_WIDTH/8;
    rect.h = SCREEN_WIDTH/8;

    // chess board annotation (black top):
    // string board_state = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

    map<char, int> chartoint = {
        {'r',0},
        {'n',1},
        {'b',2},
        {'q',3},
        {'k',4},
        {'p',5},
        {'R',6},
        {'N',7},
        {'B',8},
        {'Q',9},
        {'K',10},
        {'P',11}
    };

    int columm = 0;
    int row = 0;
    char local_char;
    int local_char_int;
    for(size_t i = 0; i<board_state.length();i++){
        local_char = board_state[i];
        if(local_char=='/'){
            columm = columm + 1;
            row = 0;
        }
        else if(isalpha(local_char)){
            rect.x = row*SCREEN_WIDTH/8;
            rect.y = columm*SCREEN_WIDTH/8;
            row = row + 1;
            m_texture = SDL_CreateTextureFromSurface(m_renderer, m_images[chartoint[board_state[i]]]);
            SDL_RenderCopy(m_renderer,m_texture,NULL,&rect);
        }
        else if(isdigit(local_char)){
            // -1 since rows start at 0
            local_char_int = (int)local_char -48;
            row = row + local_char_int;
        }
        else {
            cout<<"error"<<endl;
        }
    }
    SDL_RenderPresent(m_renderer); 
}


void Screen::update(string board){
    draw_board();
    draw_pieces(board);

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