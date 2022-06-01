#ifndef UI_H
#define UI_H

#include "SDL2/SDL.h"

class Texture;
class Game;

class UI {
public:
    UI(Game* j);
    void render();
    
private:

    //miTransform tr;

    void renderPuntosActuales();
    void renderVictoriasActuales();
    void renderTurno();
    void renderFinRonda();
    void renderNombres();
    //void renderVictoria();
    void renderEsperandoConexion();
    
    Game* juego;
};

#endif    