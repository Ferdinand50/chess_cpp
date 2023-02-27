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
    SDL_Surface * m_images[12];
    bool m_second_click;
    int m_current_click[2];
    int m_previous_click[2];
    

public:
    Screen();
    bool init();
    void update(string board);
    void draw_board();
    void draw_pieces(string board_state);
    bool processEvents();
    void close();
};

}

#endif