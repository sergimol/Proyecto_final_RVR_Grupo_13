#include "Fondo.h"
#include "sdlutils/Texture.h"
#include "sdlutils/SDLUtils.h"
#include "utils/Vector2D.h"


Fondo::Fondo(Texture* t, Texture* b)
{
    fondoTex = t;
    barajaTex = b;
    /*tr.pos = Vector2D(0,0);
    tr.scale = Vector2D(sdlutils().width(), sdlutils().height());
    tr.rot = 0;*/
}

void Fondo::render()
{
    // FONDO
    Vector2D pos(0.0f,0.0f);
    SDL_Rect dest = build_sdlrect(pos, sdlutils().width(), sdlutils().height());
    fondoTex->render(dest, 0);

    // BARAJA
    Vector2D pos(sdlutils().width()/4*3, sdlutils().height()/2);
    SDL_Rect dest = build_sdlrect(pos, 100, 150);
    fondoTex->render(dest, 90);
}

