#ifndef PLAYER_H
#define PLAYER_H

#include "ecs/Component.h"
#include "components/Carta.h"
#include "Game.h"
#include "sdlutils/InputHandler.h"

class Player : public Component {
public:
    Player(int n, Game* j) : numero(n), juego(j) {};

private:
    Game* juego;
    int numero;
    bool plantado = false;
    bool enTurno = false;
    std::vector<Carta> mano;
    int puntos = 0;
    int victorias = 0;

    void pideCarta(){
        Carta nueva = juego->getCarta();

        puntos += nueva.getValor();
        mano.push_back(nueva);

        enTurno = false;
    }

    void procesaTurno(){
        enTurno = true;
        while(enTurno){
            if(ih().isKeyDown(SDLK_SPACE)){
                pideCarta();
            }
            else if(ih().isKeyDown(SDLK_r)){
                plantado = true;
                enTurno = false;
            }
        }
    }

    void reset(int ganador){
        mano.clear();
        puntos = 0;
        plantado = false;
        if(ganador == numero)
            victorias++;
    }

    bool sigueJugando() { return !plantado; }
};

#endif