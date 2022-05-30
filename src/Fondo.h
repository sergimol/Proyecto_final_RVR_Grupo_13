#ifndef FONDO_H
#define FONDO_H

#include "SDL2/SDL.h"

class Texture;
class Game;

class Fondo {
public:
    Fondo(Texture* t, Texture* b, Game* j);
    void render();
    
private:

    Texture* fondoTex;
    Texture* barajaTex;

    Game* juego;

    int fils = 4;	
    int cols = 15;

    //miTransform tr;
};

#endif    