#include "Fondo.h"
#include "sdlutils/Texture.h"
#include "sdlutils/SDLUtils.h"
#include "utils/Vector2D.h"


Fondo::Fondo(Texture* t)
{
    fondoTex = t;
    /*tr.pos = Vector2D(0,0);
    tr.scale = Vector2D(sdlutils().width(), sdlutils().height());
    tr.rot = 0;*/
}

void Fondo::render()
{
    Vector2D pos(0.0f,0.0f);
    SDL_Rect dest = build_sdlrect(pos, sdlutils().width(), sdlutils().width());
    fondoTex->render(dest, 0);
}

