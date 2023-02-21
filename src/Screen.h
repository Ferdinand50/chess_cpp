#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

namespace caveofprogramming {

class Screen {
public:
    const static int SCREEN_WIDTH = 1600;
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture; 
    Uint32 *m_buffer; 
    

public:
    Screen();
    bool init();
    void update();
    void draw_board();
    void draw_pieces();
    bool processEvents();
    void close();
};

}

#endif