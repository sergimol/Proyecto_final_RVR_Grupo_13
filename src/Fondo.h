#ifndef FONDO_H
#define FONDO_H

#include "SDL2/SDL.h"

class Texture;

class Fondo {
public:
    Fondo(Texture* t);
    void render();
    
private:

    Texture* fondoTex;
    //miTransform tr;
};

#endif    