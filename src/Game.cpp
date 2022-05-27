#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Game.h"
Game::Game(){

}

Game::~Game(){
    // destroy texture
    SDL_DestroyTexture(tex);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
}

void Game::init(int w, int h){

    width_ = w;
    height_ = h;
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("error initializing SDL: %s\n", SDL_GetError());

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags)
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        
    win = SDL_CreateWindow("GAME", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       width_, height_, 0);
 
    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    
    // creates a renderer to render our images
    rend = SDL_CreateRenderer(win, -1, render_flags);
 
    SDL_RenderPresent(rend);
}

void Game::start(){
    // animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_QUIT:
                // handling of close button
                close = true;
                break;

            case SDL_KEYDOWN:
                break;
            }
        }

        // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

        SDL_RenderClear(rend);
                                    //full red
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);

        SDL_Rect r;
        r.x = 50;
        r.y = 50;
        r.w = 150;
        r.h = 150;

        // Set render color to blue ( rect will be rendered in this color )
        SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);

        // Render rect
        SDL_RenderFillRect(rend, &r);

        // clears the screen
        SDL_RenderCopy(rend, tex, NULL, &dest);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
}



