#include "Fondo.h"
#include "sdlutils/Texture.h"
#include "sdlutils/SDLUtils.h"
#include "utils/Vector2D.h"
#include "Game.h"


Fondo::Fondo(Texture* t, Texture* b, Game* j)
{
    fondoTex = t;
    barajaTex = b;
    juego = j;
}

void Fondo::render()
{
    // FONDO
    Vector2D pos(0.0f,0.0f);
    SDL_Rect dest = build_sdlrect(pos, sdlutils().width(), sdlutils().height());
    fondoTex->render(dest, 0);

    // BARAJA
    int numCartas = juego->getNumCartas();
    int sum = 0;
    for(int i = 0; i < numCartas - 35; i++)
    {
        Vector2D posCarta(sdlutils().width()/4*3 - sum, sdlutils().height()/4);
        auto w = barajaTex->width() / cols;
        auto h = barajaTex->height() / fils;
        SDL_Rect src = { 0, 0, w, h };
        SDL_Rect destBaraja = build_sdlrect(posCarta, 200, 250);
        barajaTex->render(src, destBaraja, 0);
        sum+=5;
    }
    
}

