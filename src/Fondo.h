#ifndef FONDO_H
#define FONDO_H

#include "SDL2/SDL.h"

class Texture;

class Fondo {
public:
    Fondo(Texture* t, Texture* b);
    void render();
    
private:

    Texture* fondoTex;
    Tecture* barajaTex;
    //miTransform tr;
};

#endif    